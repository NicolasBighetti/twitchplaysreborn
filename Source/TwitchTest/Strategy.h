// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "BlockingQueue.h"

/**
 * 
 */
class TWITCHTEST_API Strategy
{
public:

	Strategy(BlockingQueue<FString>* q);

	BlockingQueue<FString>* queue;
	TMap<FString, FString> Messages;

	virtual void Receive();
	virtual void OnTick();

};
