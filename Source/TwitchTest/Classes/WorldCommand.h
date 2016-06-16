// Fill out your copyright notice in the Description page of Project Settings.
#include "TwitchPlaysAPI.h"
#include "Command.h"
#include "GameContext.h"

#pragma once

/**
 * 
 */
class FWorldCommand : public FCommand
{

protected:
	UWorld* World;
	GameContext* Context;

public:
	FWorldCommand(FString _name, UWorld* _world, GameContext* _context) 
		: FCommand(_name), World(_world), Context(_context) {}
};
