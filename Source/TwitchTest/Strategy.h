// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "BlockingQueue.h"

/**
 * 
 */
class TWITCHTEST_API Strategy
{
public:

	Strategy(BlockingQueue<FString>* q, TMap<FString, FString>* m);

	BlockingQueue<FString>* queue;
	TMap<FString, FString>* Messages;

	virtual void Receive(FString userName, FString message);
	virtual void OnTick();

};
