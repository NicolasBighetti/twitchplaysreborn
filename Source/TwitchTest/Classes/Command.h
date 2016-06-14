// Fill out your copyright notice in the Description page of Project Settings.
#include "TwitchPlaysAPI.h"

#pragma once

class TWITCHTEST_API FCommandParser
{
private:
	FString UserName;
	TArray<FString> Args;
	int32 Index = 0;

public:
	FCommandParser(FString _username = TEXT(""), FString _cmd = TEXT(""));

	FString Get(int32 index);
	FString GetUserName();
	FString GetName();
	FString Next();
	int32 NextInt();
	float NextFloat();
};


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
	virtual void Execute(FCommandParser parser) = 0;
};
