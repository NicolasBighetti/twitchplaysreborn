// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "Strategy.h"

/**
 * Anarchy implementation of the Strategy.
 */
class Anarchy : public Strategy
{
private:
	// World timer
	FTimerHandle TimerHandle;
	
	// Unreal World
	UWorld* world;

public:
	Anarchy(UWorld* _world, BlockingQueue<FCommandParser>* _queue, int32 time, GameContext* _context) 
		: Strategy(_queue, _context), world(_world)
	{
		// Declare delegate for timer
		FTimerDelegate del;
		del.BindLambda([this] {
			OnTick();
		});
		
		// Start the timer
		world->GetTimerManager().SetTimer(TimerHandle, del, time, true);
	};

	// Override methods
	void Receive(FCommandParser parser) override;
	void OnTick() override;
};
