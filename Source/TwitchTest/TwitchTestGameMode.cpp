#include "TwitchTest.h"
#include "TwitchTestGameMode.h"
#include "BallGameContext.h"

GameContext* ATwitchTestGameMode::CreateContext()
{
	// Override default context
	return new BallGameContext();
}

void ATwitchTestGameMode::RegisterWorldCommands()
{
	Super::RegisterWorldCommands();

	// TODO : Add custom ball world commands
	// FWorldCommandRegistry::GetInstance()->Register(new FMyBallCommand(GetWorld(), Context));
}

void ATwitchTestGameMode::BeginPlay()
{
	Super::BeginPlay();
}

void ATwitchTestGameMode::BeginDestroy()
{
	Super::BeginDestroy();
}
