// Fill out your copyright notice in the Description page of Project Settings.

#include "TwitchPlaysAPI.h"
#include "Ball.h"
#include "CommandRegistry.h"
#include "BallCommands.h"

// Sets default values
ABall::ABall() : ATwitchPawn()
{
	// Create a dummy root component we can attach things to.
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));

	// Create a camera and a visible object
	UCameraComponent* OurCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("OurCamera"));
	OurVisibleComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("OurVisibleComponent"));

	// Attach our camera and visible object to our root component. Offset and rotate the camera.
	OurCamera->AttachTo(RootComponent);
	OurCamera->SetRelativeLocation(FVector(-250.0f, 0.0f, 250.0f));
	OurCamera->SetRelativeRotation(FRotator(-45.0f, 0.0f, 0.0f));
	OurVisibleComponent->SetSimulatePhysics(true);
	/*
	OurVisibleComponent->bGenerateOverlapEvents = true;
	OurVisibleComponent->SetNotifyRigidBodyCollision(true);
	OurVisibleComponent->BodyInstance.SetCollisionProfileName("PhysicsBody");
	OurVisibleComponent->OnComponentHit.AddDynamic(this, &ABall::onHit);
	*/
	OurVisibleComponent->AttachTo(RootComponent);
}

void ABall::RegisterCommands()
{
	// Register commands
	CommandsRegistry.Register(new FBallLeftCommand(this));
	CommandsRegistry.Register(new FBallRightCommand(this));
	CommandsRegistry.Register(new FBallBackwardCommand(this));
	CommandsRegistry.Register(new FBallForwardCommand(this));
	//CommandsRegistry.Register(new FBallJumpCommand(this));
}

void ABall::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ABall::Tick( float DeltaTime )
{
	Super::Tick(DeltaTime);
	// Velocity computing
	if (!CurrentVelocity.IsZero())
	{
		FVector NewLocation = GetActorLocation() + (CurrentVelocity * DeltaTime);
		SetActorLocation(NewLocation);
	}

	// Call tick from twitch pawn
}

void ABall::onHit(AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector v, const FHitResult& Hit)
{
	this->GetOurVisibleComponent()->AddImpulse(v *= FVector(10, 10, 10));
}

void ABall::BeginDestroy()
{
	Super::BeginDestroy();
	UE_LOG(LogTemp, Warning, TEXT("Ball: BeginDestroy"));
}
