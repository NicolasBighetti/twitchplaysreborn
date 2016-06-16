#include "TwitchPlaysAPI.h"
#include "TwitchGameMode.h"
#include "TwitchTestGameMode.generated.h"

#pragma once

UCLASS()
class ATwitchTestGameMode : public ATwitchGameMode
{
	GENERATED_BODY()

public:
	virtual void BeginPlay() override;
	virtual void BeginDestroy() override;

	// Default game context, to override
	virtual GameContext* CreateContext() override;

	// Default world commands, to override
	virtual void RegisterWorldCommands() override;
};
