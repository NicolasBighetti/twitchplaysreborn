// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "TwitchPlaysAPI.h"
/**
 * 
 */
class TWITCHTEST_API TwitchEventListener
{
public:

	virtual void updateSpam(int winningTeam, int strenght) {
		UE_LOG(LogTemp, Warning, TEXT("updateSpam generique"));
	}
	virtual void updateCloudWord(TArray<FString> result) = 0;


	virtual void print() {
		UE_LOG(LogTemp, Warning, TEXT("print test eventlistener"));
	}
};
