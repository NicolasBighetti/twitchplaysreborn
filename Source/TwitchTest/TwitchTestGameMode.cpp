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
	FTwitchMessageReceiver TwitchRunnable(
		TEXT(OAUTH),    // Authentication token
		TEXT(NICKNAME), // Bot nickname
		TEXT(CHANNEL)   // Channel to join
	);

	// Create thread and run thread
	UE_LOG(LogTemp, Warning, TEXT("Game mode: Starting the thread"));
	TwitchThread = FRunnableThread::Create(&TwitchRunnable, TEXT("FTwitchMessageReceiver"), 0, TPri_BelowNormal);
}

void ATwitchTestGameMode::BeginDestroy()
{
	UE_LOG(LogTemp, Warning, TEXT("Game mode: BeginDestroy"));

	// Kill the thread
	if(TwitchThread != NULL)
		TwitchThread->Kill(true);
}

// ==============

void ReceivedChatMessage(FString userName, FString message)
{
	UE_LOG(LogTemp, Warning, TEXT("%s: %s"), *userName, *message);
}
