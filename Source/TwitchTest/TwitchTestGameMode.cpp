#include "TwitchTest.h"
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


	StrategyMap.Add(TEXT("basic"), STRAT_BASIC);
	StrategyMap.Add(TEXT("anarchy"), STRAT_ANARCHY);

	// Configuration file
	Config c = Config();
	c.Load("Source/config.txt");


	// Initialize context
	Context = CreateContext();
	this->RegisterWorldCommands();
	/*
	Registry::Keys->Add(TEXT("join"));
	FCommandRegistry<>::World()->Register(new FJoinWorldCommand(GetWorld(), Context));
	for (FString m : Registry::Keys->Array()) {
		UE_LOG(LogTemp, Warning, TEXT("keys test %s"), *m);
	}
	*/

	// Initialize actors
	for (TActorIterator<ATwitchPawn> ActorItr(GetWorld()); ActorItr; ++ActorItr)
	{
		// Same as with the Object Iterator, access the subclass instance with the * or -> operators.
		ATwitchPawn *actor = *ActorItr;
		UE_LOG(LogTemp, Warning, TEXT("%s"), *(ActorItr->GetName()));

		Camps* c = new Camps(TEXT("boule"));
		Context->GetCamps()->AddCamps(c);
		ActorItr->setCamps(c);
		//ActorItr->setQueue(campsManager.getQueueInit());
		ActorItr->launch();
	}

	// Create Twitch runnable
	UE_LOG(LogTemp, Warning, TEXT("AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA"));

	TwitchRunnable = new FTwitchMessageReceiver(
		c.Get("oAuth"),    // Authentication token
		c.Get("botNickname"), // Bot nickname
		c.Get("channel"),   // Channel to join
		GetWorld(),
		Context,
		Context->GetStrategy() //ANARCHY
	);

	// Create thread and run thread
	UE_LOG(LogTemp, Warning, TEXT("Game mode: Starting the thread"));
	TwitchThread = FRunnableThread::Create(TwitchRunnable, TEXT("FTwitchMessageReceiver"), 0, TPri_BelowNormal);

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
	//FWorldCommandRegistry::GetInstance()->Register(new FJoinWorldCommand(GetWorld(), Context));
	//FWorldCommandRegistry::GetInstance()->Register(new FChangeStrategyWorldCommand(GetWorld(), Context));
	// FWorldCommandRegistry::GetInstance()->Register(new FMyBallCommand(GetWorld(), Context));
}

int32 ATwitchTestGameMode::FindStrategy(FString strategyName) {

	return StrategyMap.FindRef(strategyName);

}



void ATwitchTestGameMode::BeginDestroy()
{
	Super::BeginDestroy();
}
