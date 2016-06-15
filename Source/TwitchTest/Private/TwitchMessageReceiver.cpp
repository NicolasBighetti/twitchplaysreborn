// Fill out your copyright notice in the Description page of Project Settings.
#include "TwitchPlaysAPI.h"
#include <string>
#include "Networking.h"
#include "TwitchMessageReceiver.h"
#include "CommandRegistry.h"

#define SOCKET_NAME "TwitchListener"
#define SOCKET_HOST "irc.twitch.tv"
#define SOCKET_PORT 6667

// Initialize queue
TQueue<FString> FTwitchMessageReceiver::MessagesQueue;
BlockingQueue<FCommandParser>FTwitchMessageReceiver::Queue;

FTwitchMessageReceiver::FTwitchMessageReceiver(Config* _conf, UWorld* _world, GameContext* _context, int32 _strategy)
	: Conf(_conf), Context(_context)
{
	Channel = Conf->Get("channel");
	Tick = FCString::Atoi(*Conf->Get("tick"));

	if (_strategy == STRAT_ANARCHY) {
		UE_LOG(LogTemp, Warning, TEXT("Strategy : Anarchy"));
		Strat = new Anarchy(_world, &Queue, Tick, Context);
	}
	else if (_strategy == STRAT_DEMOCRACY) {
		UE_LOG(LogTemp, Warning, TEXT("Strategy : Democraty"));
		Strat = new Democracy(_world, &Queue, Tick, Context);
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("Strategy : Basic"));
		Strat = new Strategy(&Queue, Context);
	}
}

bool FTwitchMessageReceiver::Init()
{
	UE_LOG(LogTemp, Warning, TEXT("Twitch receiver: Init"));

	// Load banned words list
	FString bannedWordsFile = FPaths::GameDir() + Conf->Get("bannedWordsFile");

	// Failed to read file
	if (!FFileHelper::LoadANSITextFileToStrings(*bannedWordsFile, NULL, BannedWords))
		return false;

	return true;
}

uint32 FTwitchMessageReceiver::Run()
{
	UE_LOG(LogTemp, Warning, TEXT("Twitch receiver: Run"));

	// Connect to twitch
	Connect();

	// Permanently receive messages
	while (KeepReceivingMessage)
		ReceiveMessage();

	return EXIT_SUCCESS;
}

void FTwitchMessageReceiver::Stop()
{
	UE_LOG(LogTemp, Warning, TEXT("Twitch receiver: Stop"));

	int i;
	for (i = 1; i <= Context->GetCamps()->GetNbCamps(); i++) {
		UE_LOG(LogTemp, Warning, TEXT("Liste des joueurs du camp %d :"), i);
		Context->GetCamps()->getCamps(i)->DisplayTeam();
	}

	// Close and destroy socket
	KeepReceivingMessage = false;
	ListenerSocket->Close();
	ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM)->DestroySocket(ListenerSocket);
}

// =================

void FTwitchMessageReceiver::Connect()
{
	// Resolve Twitch hostname
	auto resolveInfo = ISocketSubsystem::Get()->GetHostByName(SOCKET_HOST);
	while (!resolveInfo->IsComplete());

	// Check host result
	if (resolveInfo->GetErrorCode() != 0)
	{
		UE_LOG(LogTemp, Warning, TEXT("Couldn't resolve hostname."));
		return;
	}

	// Get host IP
	const FInternetAddr* addr = &resolveInfo->GetResolvedAddress();
	uint32 OutIP = 0;
	addr->GetIp(OutIP);
	int32 port = SOCKET_PORT;

	// Configure and create socket
	TSharedRef<FInternetAddr> iaddr = ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM)->CreateInternetAddr();
	iaddr->SetIp(OutIP);
	iaddr->SetPort(SOCKET_PORT);
	ListenerSocket = ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM)->CreateSocket(NAME_Stream, TEXT(SOCKET_NAME), false);

	// Try socket connection
	bool connected = ListenerSocket->Connect(*iaddr);
	if (connected) {
		UE_LOG(LogTemp, Warning, TEXT("Connected"));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Failed to connect."));
		if (ListenerSocket)
			ListenerSocket->Close();
		return;
	}

	// Send OAuth authentication token
	SendMessage(TEXT("PASS oauth:") + Conf->Get("oAuth"));

	// Configure bot and make it joins
	SendMessage(TEXT("NICK ") + Conf->Get("botNickname"));
	SendMessage(TEXT("JOIN ") + Channel);

	// Display a message to check the bot is online
	SendMessage(TEXT("PRIVMSG ") + Channel + TEXT(" :Bot activated !"));
}

void FTwitchMessageReceiver::ReceiveMessage()
{
	TArray<uint8> ReceivedData;
	uint32 Size;
	bool Received = false;

	// Wait to receive a message
	while (ListenerSocket->HasPendingData(Size))
	{
		Received = true;
		ReceivedData.SetNumUninitialized(FMath::Min(Size, 65507u));

		int32 Read = 0;
		ListenerSocket->Recv(ReceivedData.GetData(), ReceivedData.Num(), Read);
	}

	// Check if message received
	if (Received)
	{
		// Read the message and parse it
		const std::string cstr(reinterpret_cast<const char*>(ReceivedData.GetData()), ReceivedData.Num());
		FString fs(cstr.c_str());
		ParseMessage(fs);
	}
}

void FTwitchMessageReceiver::ParseMessage(FString msg)
{
	TArray<FString> lines;
	msg.ParseIntoArrayLines(lines);
	for (FString fs : lines)
	{
		TArray<FString> parts;
		fs.ParseIntoArray(parts, TEXT(":"));
		TArray<FString> meta;
		parts[0].ParseIntoArrayWS(meta);
		if (parts.Num() >= 2)
		{
			if (meta[0] == TEXT("PING"))
			{
				SendMessage(TEXT("PONG :tmi.twitch.tv"));
			}
			else if (meta.Num() == 3 && meta[1] == TEXT("PRIVMSG"))
			{
				FString message = parts[1];
				if (parts.Num() > 2)
				{
					for (int i = 2; i < parts.Num(); i++)
					{
						message += TEXT(":") + parts[i];
					}
				}
				FString username;
				FString tmp;
				meta[0].Split(TEXT("!"), &username, &tmp);

				// Callback when message received
				ReceivedChatMessage(username, message);
				continue;
			}
			/*
			else
			{
				UE_LOG(LogTemp, Warning, TEXT("Unknown message received: %s"), *msg);
			}
			*/
		}
	}
}

// =================

bool FTwitchMessageReceiver::SendMessage(FString msg)
{
	FString serialized = msg + TEXT("\r\n");
	TCHAR *serializedChar = serialized.GetCharArray().GetData();
	int32 size = FCString::Strlen(serializedChar);
	int32 sent = 0;

	return ListenerSocket->Send((uint8*)TCHAR_TO_UTF8(serializedChar), size, sent);
}

void FTwitchMessageReceiver::ReceivedChatMessage(FString userName, FString message)
{
	UE_LOG(LogTemp, Warning, TEXT("Chat message received-> %s: %s"), *userName, *message);

	// Check banned words
	ManagedChat(userName, message, "Don't use this word (put timeout command here)");

	// Parse command
	FCommandParser parser(userName, message);
	UE_LOG(LogTemp, Warning, TEXT("commande: %s"), *parser.GetName());
	//FCommandRegistry::PrintKeywords();
	// Check if command exists
	if (!FCommandRegistry::ExistsCommand(parser.GetName()))
	{
		if (Events!=NULL) {
			if (Events->isRunning()) {
				Events->receiveMessage(userName, message);
			}
		}
		else
		UE_LOG(LogTemp, Warning, TEXT("Ball-> Unknown command: %s"), *(parser.GetName()));
		return;
	}
	UE_LOG(LogTemp, Warning, TEXT("commande connue %s"), *(parser.GetName()));

	// Check if this is a world command
	FCommand* worldCmd = FCommandRegistry::World()->Get(parser.GetName());
	if (worldCmd != NULL)
	{
		UE_LOG(LogTemp, Warning, TEXT("is world command %s"), *(parser.GetName()));
		// Execute world command
		worldCmd->Execute(parser);
		return;
	}

	UE_LOG(LogTemp, Warning, TEXT("send %s"), *(parser.GetName()));
	// Send command to strategy
	Strat->Receive(parser);
}


bool FTwitchMessageReceiver::setEvent(TwitchEvent* _event) {
	UE_LOG(LogTemp, Warning, TEXT("set event"));
	if (!Events || !Events->isRunning()) {
		UE_LOG(LogTemp, Warning, TEXT("event not register"));
		Events = _event;
		return true;
	}
	return false;
}



void FTwitchMessageReceiver::ManagedChat(FString userName, FString message, FString command) {
	// Parse message in words
	TArray<FString> messageParts;
	message.ParseIntoArray(messageParts, TEXT(" "));

	int nbWords = messageParts.Num();

	// Check every words
	for (int i = 0; i < nbWords; i++) {
		// Check if the word is banished
		if(BannedWords.Contains(messageParts[i]))
			// Send message to say word is banned
			SendMessage(
				TEXT("PRIVMSG ") + Channel + TEXT(" :") + command + TEXT(" ") + userName
			);
	}
}
