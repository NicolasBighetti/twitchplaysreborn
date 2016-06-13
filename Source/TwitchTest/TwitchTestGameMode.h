#include "TwitchTest.h"
#include "BlockingQueue.h"
#include "GameContext.h"
#include "CommandRegistry.h"
#include "WorldCommands.h"
#include "Config.h"
#include "TwitchTestGameMode.generated.h"

UCLASS()
class TWITCHTEST_API ATwitchTestGameMode : public AGameMode
{
	GENERATED_BODY()

private:
	FRunnable *TwitchRunnable = NULL;
	FRunnableThread* TwitchThread = NULL;
	GameContext* Context = NULL;
	Config Conf;

public:
	ATwitchTestGameMode();

	// Unreal Engine overrides
	virtual void BeginPlay() override;
	virtual void BeginDestroy() override;

	// Default game context, to override
	GameContext* CreateContext() { return new GameContext(); };

	// Default world commands, to override
	void RegisterWorldCommands() { 
		FWorldCommandRegistry::GetInstance()->Register(new FJoinWorldCommand(GetWorld(), Context));
	};
};
