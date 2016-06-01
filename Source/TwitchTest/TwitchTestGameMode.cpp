#include "TwitchTest.h"
#include "TwitchTestGameMode.h"
#include "FTwitchMessageReceiver.h"

#define OAUTH	 "22jwdnv3dqhmuc9t4wf6du0qq9q2td"
#define NICKNAME "drym_tv"
#define CHANNEL	 "#drymfr"

void ATwitchTestGameMode::BeginPlay()
{
	Super::BeginPlay();

	// Create Twitch runnable
	UE_LOG(LogTemp, Warning, TEXT("Game mode: Creating the runnable"));
	TwitchRunnable = new FTwitchMessageReceiver(
		TEXT(OAUTH),    // Authentication token
		TEXT(NICKNAME), // Bot nickname
		TEXT(CHANNEL)   // Channel to join
	);

	// Create thread and run thread
	UE_LOG(LogTemp, Warning, TEXT("Game mode: Starting the thread"));
	TwitchThread = FRunnableThread::Create(TwitchRunnable, TEXT("FTwitchMessageReceiver"), 0, TPri_BelowNormal);
}

void ATwitchTestGameMode::BeginDestroy()
{
	Super::BeginDestroy();
	UE_LOG(LogTemp, Warning, TEXT("Game mode: BeginDestroy"));

	// Kill the thread
	if (TwitchThread)
	{
		TwitchRunnable->Stop();
		TwitchThread->WaitForCompletion();
		delete TwitchRunnable;
	}
}
