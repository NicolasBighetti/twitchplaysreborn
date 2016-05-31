#include "TwitchTest.h"
#include <string>

#include "TwitchTestGameMode.h"

#define _SERVER "irc.chat.twitch.tv"

void ATwitchTestGameMode::BeginPlay()
{
	Super::BeginPlay();

	SendLogin();
}

void ATwitchTestGameMode::SocketListener()
{
	TArray<uint8> ReceivedData;
	uint32 Size;
	bool Received = false;
	while (ListenerSocket->HasPendingData(Size))
	{
		Received = true;
		ReceivedData.SetNumUninitialized(FMath::Min(Size, 65507u));

		int32 Read = 0;
		ListenerSocket->Recv(ReceivedData.GetData(), ReceivedData.Num(), Read);
	}
	if (Received)
	{
		const std::string cstr(reinterpret_cast<const char*>(ReceivedData.GetData()), ReceivedData.Num());
		FString fs(cstr.c_str());

		ParseMessage(fs);
	}
}

void ATwitchTestGameMode::ParseMessage(FString msg)
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
				SendString(TEXT("PONG :tmi.twitch.tv"));
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
				ReceivedChatMessage(username, message);
				continue;
			}
		}
	}
}


void ATwitchTestGameMode::ReceivedChatMessage(FString UserName, FString message)
{
	UE_LOG(LogTemp, Warning, TEXT("%s: %s"), *UserName, *message);
	SendString(TEXT("PRIVMSG #drymfr :Stop speak Kappa"));
}

void ATwitchTestGameMode::SendLogin()
{
	//On recupere les informations du serveur
	auto ResolveInfo = ISocketSubsystem::Get()->GetHostByName(_SERVER);
	
	//while (!ResolveInfo->IsComplete());

	if (ResolveInfo->GetErrorCode() != 0)
	{
		UE_LOG(LogTemp, Warning, TEXT("Couldn't resolve hostname."));
		return;
	}

	//On recupere l'adresse IP
	const FInternetAddr* Addr = &ResolveInfo->GetResolvedAddress();
	uint32 OutIP;
	Addr->GetIp(OutIP);
	int32 port = 6667;

	TSharedRef<FInternetAddr> addr = ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM)->CreateInternetAddr();
	addr->SetIp(OutIP);
	addr->SetPort(port);

	//On configure la socket
	ListenerSocket = ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM)->CreateSocket(NAME_Stream, TEXT("default"), false);

	//On se connecte
	bool connected = ListenerSocket->Connect(*addr);
	if (connected)
	{
		UE_LOG(LogTemp, Warning, TEXT("Connected."));
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("Failed to connect."));
		if (ListenerSocket)
			ListenerSocket->Close();
		return;
	}
	
	//On active le bot et on rejoint un channel
	SendString(TEXT("PASS oauth:22jwdnv3dqhmuc9t4wf6du0qq9q2td"));
	SendString(TEXT("NICK drym_tv"));
	SendString(TEXT("JOIN #drymfr"));

	//On affiche dans le channel que le bot est bien active
	SendString(TEXT("PRIVMSG #drymfr :Bot activated"));
}

bool ATwitchTestGameMode::SendString(FString msg)
{
	
	FString serialized = msg + TEXT("\r\n");
	TCHAR *serializedChar = serialized.GetCharArray().GetData();
	int32 size = FCString::Strlen(serializedChar);
	int32 sent = 0;
	
	return ListenerSocket->Send((uint8*)TCHAR_TO_UTF8(serializedChar), size, sent);
}