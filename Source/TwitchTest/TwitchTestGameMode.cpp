#include "TwitchPlaysAPI.h"
#include "TwitchTestGameMode.h"
#include "BallGameContext.h"
#include "TwitchPawn.h"
#include "TwitchMessageReceiver.h"
#include "CoreMisc.h"
#include "CommandRegistry.h"
#include "Anarchy.h"

void ATwitchTestGameMode::BeginPlay()
{
	Super::BeginPlay();
}

GameContext* ATwitchTestGameMode::CreateContext()
{
	// Override default context
	return new BallGameContext();
}

void ATwitchTestGameMode::RegisterWorldCommands()
{
	Super::RegisterWorldCommands();

	// TODO : Add custom ball world commands
	// FWorldCommandRegistry::GetInstance()->Register(new FJoinWorldCommand(GetWorld(), Context));
	// FWorldCommandRegistry::GetInstance()->Register(new FChangeStrategyWorldCommand(GetWorld(), Context));
	// FWorldCommandRegistry::GetInstance()->Register(new FMyBallCommand(GetWorld(), Context));
}

void ATwitchTestGameMode::BeginDestroy()
{
	Super::BeginDestroy();
}
