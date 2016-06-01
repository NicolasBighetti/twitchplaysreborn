#include "Networking.h"

#include "TwitchTestGameMode.generated.h"

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

	void SendLogin(FString oauth, FString UserName, FString channel);

	bool SendString(FString msg);

	void ParseMessage(FString msg);

	void ReceivedChatMessage(FString UserName, FString message);

	void ParseCommande(FString message);
};