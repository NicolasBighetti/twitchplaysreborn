// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "Hole.generated.h"

UCLASS()
class AHole : public AActor
{
	GENERATED_BODY()
	
public:	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "box")
	UBoxComponent* hitbox;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "explosion")
	UParticleSystemComponent* OurParticleSystem;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Audio Component")
	UAudioComponent* AudioComp;
	
	UFUNCTION()
	void OnBeginOverlap(class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);

	// Sets default values for this actor's properties
	AHole();
	
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;
};
