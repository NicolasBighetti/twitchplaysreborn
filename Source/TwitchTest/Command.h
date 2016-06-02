// Fill out your copyright notice in the Description page of Project Settings.
#include "TwitchTest.h"

#pragma once

/**
 * 
 */
class TWITCHTEST_API FCommand
{
protected:
	FString Name;

public:
	FCommand(FString _name) : Name(_name){}
	FString GetName() { return Name; }

	// To redefine
	virtual void Execute() = 0;
};
