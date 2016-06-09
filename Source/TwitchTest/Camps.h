// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

// #include "Commande.h"
#include "BlockingQueue.h"

using namespace std;

/**
 * 
 */
class TWITCHTEST_API Camps
{
public:

	Camps(FString* CampsName);

	bool AddPlayer(FString pseudo);

	int RemovePlayer(FString pseudo);
	bool IsInTeam(FString pseudo);

	uint32 GetTotalPlayer() {
		return TotalPlayer;
	}
	TArray<FString> GetPlayerList() {
		return Pseudo;
	}

	void SetQueue(BlockingQueue<FString> *q){
		Queue = q;
	}

	BlockingQueue<FString>* GetQueueInit()
	{
		if (isAssigned())
			return NULL;

		else {
			IsAssigned = true;
			return Queue;
		}
	}
	BlockingQueue<FString>* GetQueue()
	{

		return Queue;
	}

	void SetTQueue(TQueue<FString>* tq) {
		MessagesQueue = tq;
	}

	TQueue<FString>* GetTQueue()
	{
		if (isAssigned())
			return NULL;

		else {
			IsAssigned = true;
			return MessagesQueue;
		}
	}

	FString* GetName()
	{
		return Name;
	}

	void DisplayTeam();

private:

	TArray<FString> Pseudo;
	uint32 TotalPlayer = 0;
	FString* Name;

	TQueue<FString> *MessagesQueue;
	BlockingQueue<FString> *Queue;
	//ATwitchPawn CampsPawn;

	bool IsAssigned = false;

	bool isAssigned()
	{
		return IsAssigned;
	}
};

