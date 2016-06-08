#include "TwitchTest.h"
#include "BlockingQueue.h"
#include "CampsManager.h"
#include "TwitchTestGameMode.generated.h"

UCLASS()
class TWITCHTEST_API ATwitchTestGameMode : public AGameMode
{
	GENERATED_BODY()

private:
	FRunnable *TwitchRunnable = NULL;
	FRunnableThread* TwitchThread = NULL;

public:
	CampsManager campsManager;
	virtual void BeginPlay() override;
	virtual void BeginDestroy() override;
	void ATwitchTestGameMode::ConfigFile(FString FilPath);
	FString ATwitchTestGameMode::Parse(TArray<FString> Array, FString key);
	int32 ATwitchTestGameMode::FindStrategy(FString strategyName);
};
