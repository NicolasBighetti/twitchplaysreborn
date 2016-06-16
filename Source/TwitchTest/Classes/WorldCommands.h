// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "WorldCommand.h"

/**
* Join command.
*/
class FJoinWorldCommand : public FWorldCommand
{
public:
	FJoinWorldCommand(UWorld* _world, GameContext* _context) 
		: FWorldCommand(TEXT("join"), _world, _context) {}

	virtual void Execute(FCommandParser parser);
};


class FSpamWorldCommand : public FWorldCommand
{
public:
	FSpamWorldCommand(UWorld* _world, GameContext* _context)
		: FWorldCommand(TEXT("spam"), _world, _context) {}

	virtual void Execute(FCommandParser parser);
};

class FCloudWordCommand : public FWorldCommand
{
public:
	FCloudWordCommand(UWorld* _world, GameContext* _context)
		: FWorldCommand(TEXT("cloud"), _world, _context) {}

	virtual void Execute(FCommandParser parser);
};