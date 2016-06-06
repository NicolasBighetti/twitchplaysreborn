// Fill out your copyright notice in the Description page of Project Settings.

#include "TwitchTest.h"
#include "HoleHitBox.h"
#include "Hole.h"




// Sets default values
AHole::AHole()
{

	//RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	hitbox = CreateDefaultSubobject<UBoxComponent>(TEXT("hitbox"));
	hitbox->bGenerateOverlapEvents = true;
	hitbox->SetRelativeScale3D(FVector(2, 2, 5));
	RootComponent = hitbox;
	//hitbox->AttachTo(RootComponent);
	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("test"));
	hitbox->OnComponentBeginOverlap.AddDynamic(this, &AHole::OnBeginOverlap);

	OurParticleSystem = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("MovementParticles"));
	OurParticleSystem->AttachTo(RootComponent);
	OurParticleSystem->bAutoActivate = false;
	OurParticleSystem->SetRelativeLocation(FVector(0.0f, 0.0f, 0.0f));
	static ConstructorHelpers::FObjectFinder<UParticleSystem> ParticleAsset(TEXT("/Game/StarterContent/Particles/P_Explosion.P_Explosion"));
	if (ParticleAsset.Succeeded())
	{
		OurParticleSystem->SetTemplate(ParticleAsset.Object);
	}


	AudioComp = CreateDefaultSubobject<UAudioComponent>(TEXT("Sound"));
	if (AudioComp)
	{
		AudioComp->AttachParent = RootComponent;
		AudioComp->bAutoActivate = false; // with this true the sounds play at spawn (game starts)
	}
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

void AHole::OnBeginOverlap(class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult) {
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Balle dans le trou"));
	UE_LOG(LogTemp, Warning, TEXT("boom"));
	OurParticleSystem->Activate(false);
	AudioComp->Activate(false);

}