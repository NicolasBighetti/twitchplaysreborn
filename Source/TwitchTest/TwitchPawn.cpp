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

// Called every frame
void ATwitchPawn::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

	// Check if queue is not empty and execute command
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
}
