// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "TwitchTest.h"
#include "BlockingQueue.h"
/**
 * 
 */
class TWITCHTEST_API ThreadRead : public FRunnable
{
public:
	int32 nb_camps;
	BlockingQueue<FString>* queue;
public:
	ThreadRead(BlockingQueue<FString>* q);
	virtual bool Init();
	virtual uint32 Run();
	virtual void Stop();

};
