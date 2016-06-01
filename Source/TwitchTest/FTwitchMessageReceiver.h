// Fill out your copyright notice in the Description page of Project Settings.
#pragma once
#include "TwitchTest.h"

//typedef void(*ReceivedTwitchMessageCallback)(FString, FString);
/**
 * 
 */
class TWITCHTEST_API FTwitchMessageReceiver : public FRunnable
{
private:
	FSocket* ListenerSocket;
	FString oAuth, nickname, channel;
	bool receiveMessage = true;
	//ReceivedTwitchMessageCallback* receivedMessageCallback = NULL;

	// Twitch Connection/Reading
	void Connect();
	void ReceiveMessage();
	void ParseMessage(FString msg);

public:
	static TQueue<FString> MessagesQueue;

	// Constructor
	FTwitchMessageReceiver(FString _oAuth, FString _nickname, FString _channel)
		: oAuth(_oAuth), nickname(_nickname), channel(_channel)
	{}

	// Send and receive message in channel
	bool SendMessage(FString msg);
	void ReceivedChatMessage(FString userName, FString message);

	// Runnable interface
	virtual bool Init() override;
	virtual uint32 Run() override;
	virtual void Stop() override;
};
