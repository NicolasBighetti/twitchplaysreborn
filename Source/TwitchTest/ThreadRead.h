// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "TwitchTest.h"
#include "BlockingQueue.h"
#include "FTwitchMessageReceiver.h"
#include "CommandRegistry.h"
/**
 * 
 */
class TWITCHTEST_API ThreadRead : public FRunnable
{
public:
	bool running = true;
	int32 nb_camps;
	BlockingQueue<FString>* queue;

protected:
	// Twitch messages queue
	TQueue<FString>* CommandsQueue = &FTwitchMessageReceiver::MessagesQueue;

	// Commands registry
	FCommandRegistry<>* CommandsRegistry;

public:
	ThreadRead(FCommandRegistry<>* Commandes);
	virtual bool Init();
	virtual uint32 Run();
	virtual void Stop();
	virtual void setQueue(BlockingQueue<FString>* queue);
};
