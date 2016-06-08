#include "TwitchTest.h"
#include "TwitchTestGameMode.h"
#include "FTwitchMessageReceiver.h"
#include "CoreMisc.h"
#include "Anarchy.h"
#include "CampsManager.h"

FString oautch;
FString nickname;
FString channel;

void ATwitchTestGameMode::BeginPlay()
{
	Super::BeginPlay();

	CampsManager cmpM = CampsManager(2);

	//config file
	FString Path = "Source/config.txt";
	ConfigFile(Path);

	// Create Twitch runnable
	UE_LOG(LogTemp, Warning, TEXT("Game mode: Creating the runnable"));	

	TwitchRunnable = new FTwitchMessageReceiver(
		oautch,    // Authentication token
		nickname, // Bot nickname
		channel,   // Channel to join
		GetWorld()
		//ANARCHY
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

void ATwitchTestGameMode::ConfigFile(FString FilPath) {

	TArray<FString> Array;
	FString Config = FPaths::GameDir();
	Config += FilPath;

	//Read file
	if (FFileHelper::LoadANSITextFileToStrings(*Config, NULL, Array)) {
		//UE_LOG(LogTemp, Warning, TEXT("Config file open"));

		//Parse file from a key
		oautch = Parse(Array, "oautch");
		//UE_LOG(LogTemp, Warning, TEXT("%s"), *oautch);
		nickname = Parse(Array, "nickname");
		//UE_LOG(LogTemp, Warning, TEXT("%s"), *nickname);
		channel = Parse(Array, "channel");
		//UE_LOG(LogTemp, Warning, TEXT("%s"), *channel);
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("Could not open config file"));
	}

}

FString ATwitchTestGameMode::Parse(TArray<FString> Array, FString key) {

	int max = Array.Num();

	for (int i = 0; i < max; i++) {

		TArray<FString> parts;
		Array[i].ParseIntoArray(parts, TEXT(": "));
		TArray<FString> value;
		parts[0].ParseIntoArrayWS(value);

		if (value[0] == key) {
			parts[1].ParseIntoArrayWS(value);
			return value[0];
		}
	}

	//Fatal error
	UE_LOG(LogTemp, Fatal, TEXT("Key %s does not match"), *key);

	return "";
}
