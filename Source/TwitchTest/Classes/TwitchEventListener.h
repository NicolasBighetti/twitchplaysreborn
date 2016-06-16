// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "TwitchPlaysAPI.h"
/**
 * 
 */
class TwitchEventListener
{
public:

	virtual void updateSpam(int winningTeam, int strenght) {}
	virtual void updateCloudWord(TArray<FString> result) = 0;
};
