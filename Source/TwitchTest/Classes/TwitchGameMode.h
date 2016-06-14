#include "TwitchPlaysAPI.h"
#include "BlockingQueue.h"
#include "GameContext.h"
#include "CommandRegistry.h"
#include "WorldCommands.h"
#include "Config.h"
#include "TwitchGameMode.generated.h"

#pragma once

UCLASS()
class TWITCHTEST_API ATwitchGameMode : public AGameMode
{
	GENERATED_BODY()

private:
	FRunnable *TwitchRunnable = NULL;
	FRunnableThread* TwitchThread = NULL;
	GameContext* Context = NULL;
	Config Conf;

public:
	ATwitchGameMode();

	// Unreal Engine overrides
	virtual void BeginPlay() override;
	virtual void BeginDestroy() override;

	// Default game context, to override
	virtual GameContext* CreateContext() { return new GameContext(); };

	// Default world commands, to override
	virtual void RegisterWorldCommands() { 
		FCommandRegistry::World()->Register(new FJoinWorldCommand(GetWorld(), Context));
	};
};
