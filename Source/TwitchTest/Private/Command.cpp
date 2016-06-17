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
	if (Index + 1 < Args.Num()) {
		return Get(++Index);
	}
	else return "";
}

int32 FCommandParser::NextInt()
{
	if (Index + 1 < Args.Num()) {
		return FCString::Atoi(*Next());
	}
	else return NULL;
}

float FCommandParser::NextFloat()
{
	return FCString::Atof(*Next());
}
