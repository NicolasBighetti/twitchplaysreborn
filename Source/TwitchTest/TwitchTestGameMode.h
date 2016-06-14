#include "TwitchTest.h"
#include "BlockingQueue.h"
#include "GameContext.h"
#include "CommandRegistry.h"
#include "WorldCommands.h"
#include "Strategy.h"
#include "TwitchGameMode.h"
#include "TwitchTestGameMode.generated.h"

#pragma once

UCLASS()
class TWITCHTEST_API ATwitchTestGameMode : public ATwitchGameMode
{
	GENERATED_BODY()

private:
	FRunnable *TwitchRunnable = NULL;
	FRunnableThread* TwitchThread = NULL;
	GameContext* Context = NULL;
	TMap<FString, int32> StrategyMap;
	int32 strategy;
	

public:
	virtual void BeginPlay() override;
	virtual void BeginDestroy() override;

	int32 FindStrategy(FString strategyName);

	// Default game context, to override
	GameContext* CreateContext();

	// Default world commands, to override
	void RegisterWorldCommands();


};
