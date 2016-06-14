// Fill out your copyright notice in the Description page of Project Settings.
#pragma once
#include "TwitchPlaysAPI.h"
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
	GameContext* Context;
	FSocket* ListenerSocket;
	FString OAuth, Nickname, Channel;
	bool KeepReceivingMessage = true;
	Strategy* Strat;

	// Twitch Connection/Reading
	void Connect();
	void ReceiveMessage();
	void ParseMessage(FString msg);

public:
	static TQueue<FString> MessagesQueue;
	static BlockingQueue<FCommandParser> Queue;
	//TMap<FString, FString> Messages;

	// Constructor
	FTwitchMessageReceiver(FString _oAuth, FString _nickname, FString _channel, UWorld* _world, GameContext* _context, int32 _strategy = STRAT_BASIC)
		: OAuth(_oAuth), Nickname(_nickname), Channel(_channel), Context(_context)
	{
		if (_strategy == STRAT_ANARCHY) {
			UE_LOG(LogTemp, Warning, TEXT("Strategy : Anarchy"));
			Strat = new Anarchy(_world, &Queue, 1, Context);
		}
		else if (_strategy == STRAT_DEMOCRACY) {
			UE_LOG(LogTemp, Warning, TEXT("Strategy : Democraty"));
			Strat = new Democracy(_world, &Queue, 1, Context);
		}
		else {
			UE_LOG(LogTemp, Warning, TEXT("Strategy : Basic"));
			Strat = new Strategy(&Queue, Context);
		}
	}

	// Send and receive message in channel
	bool SendMessage(FString msg);
	void ReceivedChatMessage(FString userName, FString message);

	void FTwitchMessageReceiver::ManagedChat(FString userName, FString message, FString command);

	// Runnable interface
	virtual bool Init() override;
	virtual uint32 Run() override;
	virtual void Stop() override;

};
