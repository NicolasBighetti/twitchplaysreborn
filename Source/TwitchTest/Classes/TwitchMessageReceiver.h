// Fill out your copyright notice in the Description page of Project Settings.
#pragma once
#include "TwitchPlaysAPI.h"
#include "Config.h"
#include "BlockingQueue.h"
#include "GameContext.h"
#include "Anarchy.h"
#include "Democracy.h"

//typedef void(*ReceivedTwitchMessageCallback)(FString, FString);
/**
 * 
 */
class TWITCHTEST_API FTwitchMessageReceiver : public FRunnable
{
private:
	Config* Conf;
	GameContext* Context;
	FSocket* ListenerSocket;
	FString Channel;
	bool KeepReceivingMessage = true;
	Strategy* Strat;
	TArray<FString> BannedWords;

	// Twitch Connection/Reading
	void Connect();
	void ReceiveMessage();
	void ParseMessage(FString msg);

public:
	static TQueue<FString> MessagesQueue;
	static BlockingQueue<FCommandParser> Queue;
	//TMap<FString, FString> Messages;

	// Constructor
	FTwitchMessageReceiver(Config* _conf, UWorld* _world, GameContext* _context, int32 _strategy = STRAT_BASIC);

	// Send and receive message in channel
	bool SendMessage(FString msg);
	void ReceivedChatMessage(FString userName, FString message);

	void FTwitchMessageReceiver::ManagedChat(FString userName, FString message, FString command);

	// Runnable interface
	virtual bool Init() override;
	virtual uint32 Run() override;
	virtual void Stop() override;

};
