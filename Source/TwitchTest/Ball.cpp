// Fill out your copyright notice in the Description page of Project Settings.

#include "TwitchTest.h"
#include "Ball.h"

// Sets default values
ABall::ABall()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void ABall::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ABall::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );
	
	if (!CommandsQueue.IsEmpty())
	{
		FString cmd;
		CommandsQueue.Dequeue(cmd);
		UE_LOG(LogTemp, Warning, TEXT("Ball-> Command received: %s"), *cmd);
	}
}

// Called to bind functionality to input
void ABall::SetupPlayerInputComponent(class UInputComponent* InputComponent)
{
	Super::SetupPlayerInputComponent(InputComponent);
}

