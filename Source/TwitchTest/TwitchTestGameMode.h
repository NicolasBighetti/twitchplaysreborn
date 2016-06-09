#include "TwitchTest.h"
#include "BlockingQueue.h"
#include "GameContext.h"
#include "TwitchTestGameMode.generated.h"

UCLASS()
class TWITCHTEST_API ATwitchTestGameMode : public AGameMode
{
	GENERATED_BODY()

private:
	FRunnable *TwitchRunnable = NULL;
	FRunnableThread* TwitchThread = NULL;
	GameContext* Context = NULL;

public:
	virtual void BeginPlay() override;
	virtual void BeginDestroy() override;

	// To override
	virtual GameContext* CreateContext() { return new GameContext(); };

	// Config functions
	void ATwitchTestGameMode::ConfigFile(FString FilPath);
	FString ATwitchTestGameMode::Parse(TArray<FString> Array, FString key);
	int32 ATwitchTestGameMode::FindStrategy(FString strategyName);
};
