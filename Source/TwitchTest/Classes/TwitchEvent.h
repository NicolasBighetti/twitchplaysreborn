// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "TwitchPlaysAPI.h"
#include "GameContext.h"
#include "ActorTwitchEventListener.h"
#include "TwitchEventListener.h"
/**
 * 
 */
class TwitchEvent
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
		listener(_listener), world(_world) {};

	virtual void notify() = 0;
	virtual void receiveMessage(FString userName, FString message) = 0;

	bool isRunning() {
		return running;
	}
};
