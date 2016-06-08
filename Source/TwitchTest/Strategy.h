// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "CampsManager.h"
#include "BlockingQueue.h"

/**
 * 
 */
class TWITCHTEST_API Strategy
{
public:

	bool multicamps = true;
	Strategy(BlockingQueue<FString>* q,CampsManager* campsmanager);
	CampsManager* camps;
	BlockingQueue<FString>* queue;
	TArray<TMap<FString, FString>> Messages;

	virtual void Receive(FString userName, FString message);
	virtual void OnTick();


};
