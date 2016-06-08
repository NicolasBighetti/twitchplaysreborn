// Fill out your copyright notice in the Description page of Project Settings.
#pragma once
#include "TwitchTest.h"
#include "BlockingQueue.h"
#include "Strategy.h"
#include "CampsManager.h"
#include "Anarchy.h"

//typedef void(*ReceivedTwitchMessageCallback)(FString, FString);
/**
 * 
 */
class TWITCHTEST_API FTwitchMessageReceiver : public FRunnable
{
private:
	CampsManager* camps;
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
	//TMap<FString, FString> Messages;

	// Constructor
	FTwitchMessageReceiver(FString _oAuth, FString _nickname, FString _channel, UWorld* _pointer,CampsManager* _camps, int32 _flag = 0)
		: OAuth(_oAuth), Nickname(_nickname), Channel(_channel),camps(_camps)
	{
		UE_LOG(LogTemp, Warning, TEXT("%d , %d"), _flag, ANARCHY);
		if (_flag == ANARCHY) {
			UE_LOG(LogTemp, Warning, TEXT("Anarchy"));
			Strat = new Anarchy(_pointer, &Queue, 2,camps);
		}
		else {
			UE_LOG(LogTemp, Warning, TEXT("Basic"));
			Strat = new Strategy(&Queue,camps);
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
