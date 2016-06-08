// Fill out your copyright notice in the Description page of Project Settings.

#include "TwitchTest.h"
#include "Tunnel.h"


// Sets default values
ATunnel::ATunnel()
{
	//RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	hitbox = CreateDefaultSubobject<UBoxComponent>(TEXT("hitbox"));
	hitbox->bGenerateOverlapEvents = true;
	hitbox->SetRelativeScale3D(FVector(2, 2, 5));
	RootComponent = hitbox;

	hitbox->OnComponentBeginOverlap.AddDynamic(this, &ATunnel::OnBeginOverlap);

	OurParticleSystem = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("MovementParticles"));
	OurParticleSystem->AttachTo(RootComponent);
	OurParticleSystem->bAutoActivate = false;
	OurParticleSystem->SetRelativeLocation(FVector(0.0f, 0.0f, 0.0f));
	static ConstructorHelpers::FObjectFinder<UParticleSystem> ParticleAsset(TEXT("/Game/StarterContent/Particles/P_Explosion.P_Explosion"));
	if (ParticleAsset.Succeeded())
	{
		OurParticleSystem->SetTemplate(ParticleAsset.Object);
	}
}

// Called when the game starts or when spawned
void ATunnel::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ATunnel::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

void ATunnel::OnBeginOverlap(class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult) {

	OurParticleSystem->Activate(true);
}

