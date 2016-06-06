// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/ActorComponent.h"
#include "HoleHitBox.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TWITCHTEST_API UHoleHitBox : public UBoxComponent
{
	GENERATED_BODY()

public:	

	UPROPERTY(EditAnywhere)
	FVector size = FVector(5, 5, 5);
	// Sets default values for this component's properties
	UHoleHitBox();

	// Called when the game starts
	virtual void BeginPlay() override;
	
	/*
	virtual void TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction ) override;
	*/
		
	
};
