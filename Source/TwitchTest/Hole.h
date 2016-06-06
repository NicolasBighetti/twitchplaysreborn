// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "Hole.generated.h"

UCLASS()
class TWITCHTEST_API AHole : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AHole();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	void hit(class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	
	
};
