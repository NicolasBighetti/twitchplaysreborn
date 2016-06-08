// Fill out your copyright notice in the Description page of Project Settings.

#include "TwitchTest.h"
#include "TwitchPawn.h"


// Sets default values
ATwitchPawn::ATwitchPawn()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	// Set this pawn to be controlled by the lowest-numbered player
	AutoPossessPlayer = EAutoReceiveInput::Player0;
}


void ATwitchPawn::BeginPlay()
{
	Super::BeginPlay();
	/*
	_run = new ThreadRead(&CommandsRegistry);
	_thread = FRunnableThread::Create(_run, TEXT("FThreadRead"), 0, TPri_BelowNormal);
	*/
}

// Called every frame
void ATwitchPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// Check if queue is not empty and execute command
	/*
	if (!CommandsQueue.IsEmpty())
	{
		// Get twitch command
		FString cmd;
		CommandsQueue.Dequeue(cmd);

		UE_LOG(LogTemp, Warning, TEXT("Ball-> Executing command: %s"), *cmd);

		// Execute command
		if(!CommandsRegistry.Execute(cmd))
			// Command not found
			UE_LOG(LogTemp, Warning, TEXT("Ball-> Unknown command: %s"), *cmd);
	}
	*/
}

void ATwitchPawn::BeginDestroy()
{
	Super::BeginDestroy();
	UE_LOG(LogTemp, Warning, TEXT("Ball: BeginDestroy"));

	//Kill the thread
	if (_thread)
	{
		_run->Stop();
		_thread->WaitForCompletion();
		delete _thread;
	}
}

void ATwitchPawn::setQueue(BlockingQueue<FString>* queue)
{
	_run = new ThreadRead(&CommandsRegistry);
	_run->setQueue(queue);
}
void ATwitchPawn::launch()
{
	UE_LOG(LogTemp, Warning, TEXT("Launch Thread read"));
	_thread = FRunnableThread::Create(_run, TEXT("FThreadRead"), 0, TPri_BelowNormal);
}