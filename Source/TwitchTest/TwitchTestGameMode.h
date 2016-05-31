#pragma once

#include "GameFramework/GameMode.h"
#include "Runtime/Networking/Public/Networking.h"

#include "TwitchTestGameMode.generated.h"

/**
*
*/
UCLASS()
class TWITCHTEST_API ATwitchTestGameMode : public AGameMode
{
	GENERATED_BODY()

public:
	virtual void BeginPlay() override;

private:
	FSocket* ListenerSocket;
	FSocket* ConnectionSocket;
	FTimerHandle timerHandle;

	void SocketListener();

	void SendLogin();

	bool SendString(FString msg);

	void ParseMessage(FString msg);

	void ReceivedChatMessage(FString UserName, FString message);
};