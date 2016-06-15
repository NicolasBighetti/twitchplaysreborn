// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "TwitchPlaysAPI.h"
#include "GameContext.h"
#include "ActorTwitchEventListener.h"
#include "TwitchEventListener.h"
/**
 * 
 */
class TWITCHTEST_API TwitchEvent
{

protected:

	int32 delay;
	GameContext* Context;
	AActorTwitchEventListener* listener = NULL;
	UWorld* world;
	FTimerHandle Timer;
	bool running = true;

public:


	TwitchEvent() {}
	TwitchEvent(int32 _delay, GameContext* _context, AActorTwitchEventListener* _listener, UWorld* _world) :delay(_delay), Context(_context),
		listener(_listener),world(_world)
	{

		//launch timmer for listen to chat at the end call notify, only once
		/*
		FTimerDelegate del;
		del.BindLambda([this] {
			UE_LOG(LogTemp, Warning, TEXT("fin timmer"));
			this->notify();
		});
		world->GetTimerManager().SetTimer(TimerHandle, del, delay, false);
		*/
	};

	virtual void notify() = 0;
	virtual void receiveMessage(FString userName, FString message) = 0;

	bool isRunning() {
		UE_LOG(LogTemp, Warning, TEXT("Running event: %d"), running);
		return running;
	}
	
};
