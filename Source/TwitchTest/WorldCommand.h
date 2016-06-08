// Fill out your copyright notice in the Description page of Project Settings.
#include "TwitchTest.h"
#include "Command.h"

#pragma once

/**
 * 
 */
class TWITCHTEST_API FWorldCommand : public FCommand
{

protected:
	UWorld* World;

public:
	FWorldCommand(FString _name, UWorld* _world) : FCommand(_name), World(_world){}
};
