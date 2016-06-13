#include "TwitchTest.h"
#include "TwitchGameMode.h"
#include "TwitchPawn.h"
#include "TwitchMessageReceiver.h"
#include "CoreMisc.h"
#include "CommandRegistry.h"

#define DEFAULT_CONFIG "Source/config.txt"

ATwitchGameMode::ATwitchGameMode() {
	// Configuration file
	this->Conf = Config::Load(TEXT(DEFAULT_CONFIG));
}

void ATwitchGameMode::BeginPlay()
{
	Super::BeginPlay();

	// Initialize context
	Context = CreateContext();
	this->RegisterWorldCommands();

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
	UE_LOG(LogTemp, Warning, TEXT("Game mode: Creating runnable"));	
	TwitchRunnable = new FTwitchMessageReceiver(
		Conf.Get("oAuth"),    // Authentication token
		Conf.Get("botNickname"), // Bot nickname
		Conf.Get("channel"),   // Channel to join
		GetWorld(),
		Context,
		Strategy::FindStrategy(Conf.Get("strategy")) // Strategy to apply
	);
	
	// Create thread and run thread
	UE_LOG(LogTemp, Warning, TEXT("Game mode: Starting the thread"));
	TwitchThread = FRunnableThread::Create(TwitchRunnable, TEXT("FTwitchMessageReceiver"), 0, TPri_BelowNormal);
}

void ATwitchGameMode::BeginDestroy()
{
	Super::BeginDestroy();
	UE_LOG(LogTemp, Warning, TEXT("Game mode: BeginDestroy"));

	delete Context;

	// Kill the thread
	if (TwitchThread)
	{
		TwitchRunnable->Stop();
		TwitchThread->WaitForCompletion();
		delete TwitchRunnable;
	}
}
