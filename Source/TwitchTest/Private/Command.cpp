// Fill out your copyright notice in the Description page of Project Settings.
#include "TwitchPlaysAPI.h"
#include "Command.h"

FCommandParser::FCommandParser(FString _username, FString _cmd) : UserName(_username)
{
	_cmd.ParseIntoArray(Args, TEXT(" "));
}

FString FCommandParser::Get(int32 index)
{
	return Args[index];
}

FString FCommandParser::GetUserName()
{
	return UserName;
}


FString FCommandParser::GetName()
{
	return Get(0).ToLower();
}

FString FCommandParser::Next()
{
	return Get(++Index);
}

int32 FCommandParser::NextInt()
{
	return FCString::Atoi(*Next());
}

float FCommandParser::NextFloat()
{
	return FCString::Atof(*Next());
}
