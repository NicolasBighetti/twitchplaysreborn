// Fill out your copyright notice in the Description page of Project Settings.

#include "TwitchPlaysAPI.h"
#include "WorldCommands.h"
#include "TwitchMessageReceiver.h"
#include "CloudWordEvent.h"
#include "SpamEvent.h"

#define Val 4
#define superuser TEXT("drymfr")
/**
 * Join command.
 */
void FJoinWorldCommand::Execute(FCommandParser parser)
{
	// Add player to team
	Context->GetCamps()->AddPlayer(
		parser.GetUserName(), // Username
		//CampsManager::AUTO_STRICT, // Auto-balance
		CampsManager::MANUAL, //Without Auto-balance
		parser.NextInt() // Camp ID
	);
}

void FSpamWorldCommand::Execute(FCommandParser parser)
{
	FString user = parser.GetUserName();
	UE_LOG(LogTemp, Warning,TEXT("utilisateur de spam: %s"), *user);
	if (World != NULL && user.Equals(Context->GetAdmin())) {
		FString word = parser.Next();
		if (!word.Equals("")) {
			//executed in GameThread
			FFunctionGraphTask::CreateAndDispatchWhenReady([this, word]() {
				AActorTwitchEventListener* ActorListener = NULL;
				for (TActorIterator<AActorTwitchEventListener> ActorItr(World); ActorItr; ++ActorItr)
				{
					ActorListener = *ActorItr;
				}
				SpamEvent* events = new SpamEvent(10, Context, ActorListener, World, word);
				((FTwitchMessageReceiver*)Context->getReceiver())->setEvent(events);
			}
			, TStatId(), nullptr, ENamedThreads::GameThread);
		}
	}
}

void FCloudWordCommand::Execute(FCommandParser parser)
{
	FString user = parser.GetUserName();
	UE_LOG(LogTemp, Warning, TEXT("utilisateur de cloudword: %s"), *user);
	if (World != NULL && user.Equals(Context->GetAdmin())) {
		int32 nb = parser.NextInt();
		if (nb != NULL) {
			FFunctionGraphTask::CreateAndDispatchWhenReady([this, nb]() {
				AActorTwitchEventListener* ActorListener = NULL;
				for (TActorIterator<AActorTwitchEventListener> ActorItr(World); ActorItr; ++ActorItr)
				{
					ActorListener = *ActorItr;
				}
				CloudWordEvent* events = new CloudWordEvent(10, Context, ActorListener, World, nb);
				((FTwitchMessageReceiver*)Context->getReceiver())->setEvent(events);
			}
			, TStatId(), nullptr, ENamedThreads::GameThread);
		}
	}
}
