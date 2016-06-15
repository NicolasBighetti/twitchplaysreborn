// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "WorldCommand.h"

/**
* Join command.
*/
class TWITCHTEST_API FJoinWorldCommand : public FWorldCommand
{
public:
	FJoinWorldCommand(UWorld* _world, GameContext* _context) 
		: FWorldCommand(TEXT("join"), _world, _context) {}

	virtual void Execute(FCommandParser parser);
};


class TWITCHTEST_API FSpamWorldCommand : public FWorldCommand
{
public:
	FSpamWorldCommand(UWorld* _world, GameContext* _context)
		: FWorldCommand(TEXT("spam"), _world, _context) {}

	virtual void Execute(FCommandParser parser);
};

class TWITCHTEST_API FCloudWordCommand : public FWorldCommand
{
public:
	FCloudWordCommand(UWorld* _world, GameContext* _context)
		: FWorldCommand(TEXT("cloud"), _world, _context) {}

	virtual void Execute(FCommandParser parser);
};