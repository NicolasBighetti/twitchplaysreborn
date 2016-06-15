// Fill out your copyright notice in the Description page of Project Settings.

#include "TwitchPlaysAPI.h"
#include "SpamEvent.h"
#include "TwitchTestGameMode.h"
#include "ActorTwitchEventListener.h"


// Sets default values
AActorTwitchEventListener::AActorTwitchEventListener()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
	text = CreateDefaultSubobject<UTextRenderComponent>(TEXT("Text"));
	text->AttachTo(RootComponent);
	UE_LOG(LogTemp, Warning, TEXT("ActorListener constructor"));

}

// Called when the game starts or when spawned
void AActorTwitchEventListener::BeginPlay()
{
	Super::BeginPlay();
	UE_LOG(LogTemp, Warning, TEXT("ActorListener begin play"));
	//GetWorld()->GetAuthGameMode();
	//ATwitchTestGameMode* gm = (ATwitchTestGameMode*) GetWorld()->GetAuthGameMode();
	//SpamEvent event = SpamEvent(5, gm->getContext(), this, GetWorld(), TEXT("pd"));
}

// Called every frame
void AActorTwitchEventListener::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

void AActorTwitchEventListener::updateSpam(int winningTeam, int strenght)
{
	UE_LOG(LogTemp, Warning, TEXT("coucou %d %d"),winningTeam,strenght);
	text->SetText(FText::FromString(FString::Printf(TEXT("Winning team %d with %d spams !"), winningTeam, strenght)));
	FTimerHandle timer;
	GetWorld()->GetTimerManager().SetTimer(timer, this, &AActorTwitchEventListener::clear, clear_time, false);
}

void AActorTwitchEventListener::updateCloudWord(TArray<FString> result)
{
	int i;
	FString r = TEXT("");
	for (i = 0; i < result.Num(); i++) {
		r += TEXT(" ");
		r += result[i];
		UE_LOG(LogTemp, Warning, TEXT("Word selected: %s"), *result[i]);
	}
	text->SetText(FText::FromString(r));
	FTimerHandle timer;
	GetWorld()->GetTimerManager().SetTimer(timer, this, &AActorTwitchEventListener::clear, clear_time, false);
}

void AActorTwitchEventListener::print() {
	UE_LOG(LogTemp, Warning, TEXT("print test eventlistener dans actor"));
}


void AActorTwitchEventListener::clear() {
	text->SetText(FText::FromString(TEXT("")));
}
