#include "TwitchPlaysAPI.h"
#include "BlockingQueue.h"
#include "GameContext.h"
#include "CommandRegistry.h"
#include "WorldCommands.h"
#include "Config.h"
#include "TwitchEvent.h"
#include "SpamEvent.h"
#include "ActorTwitchEventListener.h"
#include "TwitchGameMode.generated.h"

#pragma once

UCLASS()
class ATwitchGameMode : public AGameMode
{
	GENERATED_BODY()

private:
	TwitchEvent* events;
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
		FCommandRegistry::World()->Register(new FSpamWorldCommand(GetWorld(), Context));
		FCommandRegistry::World()->Register(new FCloudWordCommand(GetWorld(), Context));
	};
};
