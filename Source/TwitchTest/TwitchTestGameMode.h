#include "TwitchTest.h"
#include "BlockingQueue.h"
#include "GameContext.h"
#include "CommandRegistry.h"
#include "WorldCommands.h"
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

	// Default game context, to override
	GameContext* CreateContext() { return new GameContext(); };

	// Default world commands, to override
	void RegisterWorldCommands() { 
		FCommandRegistry<>::World()->Register(new FJoinWorldCommand(GetWorld(), Context));
	};

	// Config functions
	void ATwitchTestGameMode::ConfigFile(FString FilPath);
	FString ATwitchTestGameMode::Parse(TArray<FString> Array, FString key);
	int32 ATwitchTestGameMode::FindStrategy(FString strategyName);
};
