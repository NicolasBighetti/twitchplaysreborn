// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Pawn.h"
#include "FTwitchMessageReceiver.h"
#include "CommandRegistry.h"
#include "TwitchPawn.generated.h"

UCLASS()
class TWITCHTEST_API ATwitchPawn : public APawn
{
	GENERATED_BODY()

protected:
	// Twitch messages queue
	TQueue<FString>& CommandsQueue = FTwitchMessageReceiver::MessagesQueue;

	// Commands registry
	FCommandRegistry CommandsRegistry;

public:
	// Sets default values for this pawn's properties
	ATwitchPawn();

	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;
};
