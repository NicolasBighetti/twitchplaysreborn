// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "TwitchPlaysAPI.h"
#include "GameFramework/Actor.h"
#include "TwitchEventListener.h"
#include "ActorTwitchEventListener.generated.h"

UCLASS()
class TWITCHTEST_API AActorTwitchEventListener : public AActor, public TwitchEventListener
{
	GENERATED_BODY()
	
public:	

	// Sets default values for this actor's properties
	AActorTwitchEventListener();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UTextRenderComponent* text;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int32 clear_time = 3;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	void updateSpam(int winningTeam, int strenght) override;
	void updateCloudWord(TArray<FString> result) override;
	virtual void print() override;
	void clear();
	
};
