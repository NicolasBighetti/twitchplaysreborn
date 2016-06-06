// Fill out your copyright notice in the Description page of Project Settings.

#include "TwitchTest.h"
#include "HoleHitBox.h"
#include "Hole.h"



// Sets default values
AHole::AHole()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	UHoleHitBox* hitbox = CreateDefaultSubobject<UHoleHitBox>(TEXT("hitbox"));
	hitbox->AttachTo(RootComponent);
	hitbox->OnComponentBeginOverlap.AddDynamic(this, &AHole::hit);

}

// Called when the game starts or when spawned
void AHole::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AHole::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

void AHole::hit(class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult) {
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Balle dans le trou"));
	UE_LOG(LogTemp, Warning, TEXT("boom"));
}