// Fill out your copyright notice in the Description page of Project Settings.

#include "TwitchTest.h"
#include "Ball.h"

// Sets default values
ABall::ABall()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	// Set this pawn to be controlled by the lowest-numbered player
	AutoPossessPlayer = EAutoReceiveInput::Player0;

	// Create a dummy root component we can attach things to.
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
	// Create a camera and a visible object
	UCameraComponent* OurCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("OurCamera"));
	OurVisibleComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("OurVisibleComponent"));
	// Attach our camera and visible object to our root component. Offset and rotate the camera.
	OurCamera->AttachTo(RootComponent);
	OurCamera->SetRelativeLocation(FVector(-250.0f, 0.0f, 250.0f));
	OurCamera->SetRelativeRotation(FRotator(-45.0f, 0.0f, 0.0f));
	OurVisibleComponent->AttachTo(RootComponent);
	//camps.SetKeyword(Commande(FString(TEXT("droite")), &ABall::Go_right));
	//camps.SetKeyword(Commande(FString(TEXT("gauche")), &ABall::Go_left));
}

// Called when the game starts or when spawned
void ABall::BeginPlay()
{
	Super::BeginPlay();
}



void ABall::Go_right() {
	CurrentVelocity.X = FMath::Clamp(1.0f, -1.0f, 1.0f) * 100.0f;
}

void ABall::Go_left() {
	CurrentVelocity.X = FMath::Clamp(-1.0f, -1.0f, 1.0f) * 100.0f;
}

// Called every frame
void ABall::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );
	if (!CurrentVelocity.IsZero())
	{
		FVector NewLocation = GetActorLocation() + (CurrentVelocity * DeltaTime);
		SetActorLocation(NewLocation);
	}
	if (!CommandsQueue.IsEmpty())
	{
		FString cmd;
		CommandsQueue.Dequeue(cmd);
		UE_LOG(LogTemp, Warning, TEXT("Ball-> Command received: %s"), *cmd);
		CurrentVelocity.X = FMath::Clamp(1.0f, -1.0f, 1.0f) * 100.0f;
		//Commande c = camps.GetCommandByKeyword(cmd);
		//c.execute();
		if (cmd.Equals(FString(TEXT("droite")))) {
			Go_right();
		}
		if (cmd.Equals(FString(TEXT("gauche")))) {
			Go_left();
		}

	}
}

// Called to bind functionality to input
void ABall::SetupPlayerInputComponent(class UInputComponent* InputComponent)
{
	Super::SetupPlayerInputComponent(InputComponent);
}
