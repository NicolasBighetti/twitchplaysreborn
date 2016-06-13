#include "TwitchTest.h"
#include "TwitchGameMode.h"
#include "TwitchTestGameMode.generated.h"

#pragma once

UCLASS()
class TWITCHTEST_API ATwitchTestGameMode : public ATwitchGameMode
{
	GENERATED_BODY()

	// Unreal Engine overrides
	virtual void BeginPlay() override;
	virtual void BeginDestroy() override;

	// Override default context
	virtual GameContext* CreateContext() override;

	// Add custom world commands
	virtual void RegisterWorldCommands() override;
};
