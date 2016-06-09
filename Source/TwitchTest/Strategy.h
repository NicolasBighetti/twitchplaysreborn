// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "GameContext.h"
#include "BlockingQueue.h"
#include "Command.h"

#define STRAT_BASIC    0
#define STRAT_ANARCHY  1

/**
 * 
 */
class TWITCHTEST_API Strategy
{
protected:
	GameContext* Context;
	BlockingQueue<FCommandParser>* queue;
	TArray<TMap<FString, FCommandParser>> Messages;
	bool multicamps = true;

public:
	Strategy(BlockingQueue<FCommandParser>* _queue, GameContext* _context);

	virtual void Receive(FCommandParser parser);
	virtual void OnTick();
};
