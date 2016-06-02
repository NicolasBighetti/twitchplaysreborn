// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Command.h"

/**
 * 
 */
class TWITCHTEST_API FCommandRegistry
{
private:
	// Commands list
	TMap<FString, FCommand*> Commands;
public:
	// FCommandRegistry();
	~FCommandRegistry();

	// Commands management
	void Register(FCommand* command);
	FCommand* Get(FString name);
	bool Execute(FString name);
};
