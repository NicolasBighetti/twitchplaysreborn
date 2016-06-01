#include "Networking.h"
#include "BlockingQueue.h"
#include "Async.h"
#include "TwitchTestGameMode.generated.h"


UCLASS()
class TWITCHTEST_API ATwitchTestGameMode : public AGameMode
{
	GENERATED_BODY()

public:
	virtual void BeginPlay() override;
	BlockingQueue<FString>* queue;
private:
	FSocket* ListenerSocket;
	FSocket* ConnectionSocket;
	FTimerHandle timerHandle;

	void SocketListener();
	void wait_message();
	void SendLogin();

	bool SendString(FString msg);

	void SendLogin(FString oauth, FString UserName, FString channel);

	void ParseMessage(FString msg);

	void ReceivedChatMessage(FString UserName, FString message);

	void ParseCommande(FString message);
};