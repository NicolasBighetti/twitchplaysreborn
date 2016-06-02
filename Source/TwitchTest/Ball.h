// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Pawn.h"
#include "TwitchPawn.h"
#include "Ball.generated.h"

UCLASS()
class TWITCHTEST_API ABall : public ATwitchPawn
{
	GENERATED_BODY()

protected:
	FVector CurrentVelocity;

	UPROPERTY(EditAnywhere)
	USceneComponent* OurVisibleComponent;

public:
	// Sets default values for this pawn's properties
	ABall();

	FVector GetCurrentVelocity() { return CurrentVelocity; }
	void SetCurrentVelocity(FVector velocity) { CurrentVelocity = velocity; }

	// Called every frame
	virtual void Tick(float DeltaSeconds) override;
};
