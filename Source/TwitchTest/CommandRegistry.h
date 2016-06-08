// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "WorldCommand.h"

/**
 * 
 */
template<class CMD = FCommand>
class TWITCHTEST_API FCommandRegistry
{
private:
	// Commands list
	TMap<FString, CMD*> Commands;
public:
	// FCommandRegistry();
	~FCommandRegistry();

	// Commands management
	void Register(CMD* command);
	CMD* Get(FString name);
	bool Execute(FString name);
	bool IsCommand(FString name);

	// World commands
	static const FCommandRegistry<FWorldCommand> World;
};
