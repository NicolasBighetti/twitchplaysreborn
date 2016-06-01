// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Pawn.h"
#include "FTwitchMessageReceiver.h"
#include "Ball.generated.h"

UCLASS()
class TWITCHTEST_API ABall : public APawn
{
	GENERATED_BODY()

private:
	TQueue<FString>& CommandsQueue = FTwitchMessageReceiver::MessagesQueue;

public:
	// Sets default values for this pawn's properties
	ABall();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;

	
	
};
