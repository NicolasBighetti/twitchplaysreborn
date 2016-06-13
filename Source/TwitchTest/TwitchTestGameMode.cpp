#include "TwitchTest.h"
#include "TwitchTestGameMode.h"
#include "TwitchPawn.h"
#include "TwitchMessageReceiver.h"
#include "CoreMisc.h"
#include "CommandRegistry.h"
#include "Anarchy.h"

FString oautch;
FString nickname;
FString channel;
int32 strategy;

void ATwitchTestGameMode::BeginPlay()
{
	Super::BeginPlay();


	StrategyMap.Add(TEXT("basic"), STRAT_BASIC);
	StrategyMap.Add(TEXT("anarchy"), STRAT_ANARCHY);

	// Configuration file
	FString Path = "Source/config.txt";
	ConfigFile(Path);


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
		oautch,    // Authentication token
		nickname, // Bot nickname
		channel,   // Channel to join
		GetWorld(),
		Context,
		strategy //ANARCHY
	);
	
	// Create thread and run thread
	UE_LOG(LogTemp, Warning, TEXT("Game mode: Starting the thread"));
	TwitchThread = FRunnableThread::Create(TwitchRunnable, TEXT("FTwitchMessageReceiver"), 0, TPri_BelowNormal);
}

void ATwitchTestGameMode::BeginDestroy()
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
		FString strategyName = Parse(Array, "strategy");
		strategy = FindStrategy(strategyName);
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

int32 ATwitchTestGameMode::FindStrategy(FString strategyName) {

	return StrategyMap.FindRef(strategyName);

 
}
