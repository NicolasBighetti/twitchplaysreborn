// Fill out your copyright notice in the Description page of Project Settings.

#include "TwitchTest.h"
#include "HoleHitBox.h"


// Sets default values for this component's properties
UHoleHitBox::UHoleHitBox()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	bWantsBeginPlay = true;
	UE_LOG(LogTemp, Warning, TEXT("creation hitbox"));
	//PrimaryComponentTick.bCanEverTick = true;
	SetBoxExtent(size, false);
	// ...
}


// Called when the game starts
void UHoleHitBox::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


/*
void UHoleHitBox::TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction )
{
	Super::TickComponent( DeltaTime, TickType, ThisTickFunction );

	// ...
}
*/

