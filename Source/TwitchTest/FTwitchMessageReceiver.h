// Fill out your copyright notice in the Description page of Project Settings.
#pragma once
#include "TwitchTest.h"
#include "BlockingQueue.h"
#include "Strategy.h"
#include "Anarchy.h"

//typedef void(*ReceivedTwitchMessageCallback)(FString, FString);
/**
 * 
 */
class TWITCHTEST_API FTwitchMessageReceiver : public FRunnable
{
private:
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
	static BlockingQueue<FString>Queue;

	// Constructor
	FTwitchMessageReceiver(FString _oAuth, FString _nickname, FString _channel, UWorld* _pointer)
		: OAuth(_oAuth), Nickname(_nickname), Channel(_channel)
	{
		//UE_LOG(LogTemp, Warning, TEXT("Avant l'anarchy"));
		Strat = new Anarchy(_pointer, &Queue);
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
