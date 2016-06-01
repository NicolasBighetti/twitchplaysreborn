// Fill out your copyright notice in the Description page of Project Settings.
#include "TwitchTest.h"
#include <string>
#include "Networking.h"
#include "FTwitchMessageReceiver.h"

bool FTwitchMessageReceiver::Init()
{
	UE_LOG(LogTemp, Warning, TEXT("Twitch thread: Init"));

	// Initialize listener socket
	FIPv4Endpoint Endpoint(FIPv4Address(127, 0, 0, 1), 6667);
	ListenerSocket = FTcpSocketBuilder(TEXT("TwitchListener"))
		.AsReusable()
		.BoundToEndpoint(Endpoint)
		.Listening(8);

	// Configure receiver socket
	int32 NewSize = 0;
	ListenerSocket->SetReceiveBufferSize(2 * 1024 * 1024, NewSize);

	return true;
}

uint32 FTwitchMessageReceiver::Run()
{
	UE_LOG(LogTemp, Warning, TEXT("Twitch thread: Run"));

	// Connect to twitch
	Connect();

	// Permanently receive messages
	while (true)
		ReceiveMessage();
}

void FTwitchMessageReceiver::Stop()
{
	UE_LOG(LogTemp, Warning, TEXT("Twitch thread: Stop"));

	// Close and destroy socket
	ListenerSocket->Close();
	ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM)->DestroySocket(ListenerSocket);
}

// =================

void FTwitchMessageReceiver::Connect()
{
	// Resolve Twitch hostname
	auto ResolveInfo = ISocketSubsystem::Get()->GetHostByName("irc.twitch.tv");
	while (!ResolveInfo->IsComplete());

	// Check host result
	if (ResolveInfo->GetErrorCode() != 0)
	{
		UE_LOG(LogTemp, Warning, TEXT("Couldn't resolve hostname."));
		return;
	}

	// Get host IP
	const FInternetAddr* Addr = &ResolveInfo->GetResolvedAddress();
	uint32 OutIP = 0;
	Addr->GetIp(OutIP);
	int32 port = 6667;

	// Configure and create socket
	TSharedRef<FInternetAddr> addr = ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM)->CreateInternetAddr();
	addr->SetIp(OutIP);
	addr->SetPort(port);
	ListenerSocket = ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM)->CreateSocket(NAME_Stream, TEXT("default"), false);

	// Try socket connection
	bool connected = ListenerSocket->Connect(*addr);
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
	SendMessage(TEXT("PASS oauth:") + oAuth);

	// Configure bot and make it joins
	SendMessage(TEXT("NICK ") + nickname);
	SendMessage(TEXT("JOIN ") + channel);

	//On affiche dans le channel que le bot est bien active
	//SendString(TEXT("PRIVMSG #drymfr :Bot activated"));
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
				//receivedMessageCallback(username, message);
				continue;
			}
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