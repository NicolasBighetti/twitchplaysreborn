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
	FTwitchMessageReceiver TwitchRunnable = FTwitchMessageReceiver(
		TEXT(OAUTH),    // Authentication token
		TEXT(NICKNAME), // Bot nickname
		TEXT(CHANNEL)   // Channel to join
	);

	// Create thread and run thread
	TwitchThread = FRunnableThread::Create(&TwitchRunnable, TEXT("FTwitchMessageReceiver"), 0, TPri_BelowNormal);
}

void ATwitchTestGameMode::BeginDestroy()
{
	// Kill the thread
	if(TwitchThread != NULL)
		TwitchThread->Kill(true);
}

// ==============

void ReceivedChatMessage(FString userName, FString message)
{
	UE_LOG(LogTemp, Warning, TEXT("%s: %s"), *userName, *message);
}
