// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "GameContext.h"
#include "BlockingQueue.h"
#include "Command.h"
#include "WorldCommand.h"

#define STRAT_BASIC    0
#define STRAT_ANARCHY  1
#define STRAT_DEMOCRACY 2

/**
 * 
 */
class Strategy
{
protected:
	GameContext* Context;
	BlockingQueue<FCommandParser>* queue;
	TArray<TMap<FString, FCommandParser>> Messages;
	bool multicamps = true;

	static TMap<FString, int32> StrategyMap;

public:
	Strategy(BlockingQueue<FCommandParser>* _queue, GameContext* _context);

	virtual void Receive(FCommandParser parser);
	virtual void OnTick();

	// === Strategy types management

	static TMap<FString, int32> BasicStrategyMap() {
		TMap<FString, int32> StratsMap;

		// Basic strategies
		StratsMap.Add(TEXT("basic"), STRAT_BASIC);
		StratsMap.Add(TEXT("anarchy"), STRAT_ANARCHY);
		StratsMap.Add(TEXT("democracy"), STRAT_DEMOCRACY);

		return StratsMap;
	}

	static int32 FindStrategy(FString strategyName) {
		return StrategyMap.FindRef(strategyName);
	}

	static void AddStrategy(FString strategyName, int32 strategy) {
		StrategyMap.Add(strategyName, strategy);
	}
};

class FChangeStrategyWorldCommand : public FWorldCommand {

public:
	FChangeStrategyWorldCommand(UWorld* _world, GameContext* _context)
		: FWorldCommand(TEXT("strat"), _world, _context) {}

	virtual void Execute(FCommandParser parser);
};