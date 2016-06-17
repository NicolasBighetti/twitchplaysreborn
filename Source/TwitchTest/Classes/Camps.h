// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

// #include "Commande.h"
#include "BlockingQueue.h"
#include "Command.h"

using namespace std;

/**
 * Camps.
 */
class Camps
{
private:
	TArray<FString> Pseudo;
	uint32 TotalPlayer = 0;
	FString Name;

	TQueue<FString> *MessagesQueue;
	BlockingQueue<FCommandParser> *Queue;
	//ATwitchPawn CampsPawn;

	bool IsAssigned = false;
public:
	Camps(FString CampsName);

	/**
      *	Adds a player to the camp.
	  */
	bool AddPlayer(FString pseudo);

	/**
      *	Removes a player from the camp.
	  */
	int RemovePlayer(FString pseudo);
	
	/**
      *	Checks if player is in the team.
	  */
	bool IsInTeam(FString pseudo);

	/**
      *	Gets total number of players.
	  */
	uint32 GetTotalPlayer() {
		return TotalPlayer;
	}
	
	/**
      *	Gets list of players.
	  */
	TArray<FString> GetPlayerList() {
		return Pseudo;
	}

	/**
      *	Sets the queue for this camp.
	  */
	void SetQueue(BlockingQueue<FCommandParser> *q){
		Queue = q;
	}

	BlockingQueue<FCommandParser>* GetQueueInit()
	{
		if (IsAssigned)
			return NULL;
		else {
			IsAssigned = true;
			return Queue;
		}
	}
	
	BlockingQueue<FCommandParser>* GetQueue()
	{
		return Queue;
	}

	void SetTQueue(TQueue<FString>* tq) {
		MessagesQueue = tq;
	}

	TQueue<FString>* GetTQueue()
	{
		if (IsAssigned)
			return NULL;

		else {
			IsAssigned = true;
			return MessagesQueue;
		}
	}

	FString GetName()
	{
		return Name;
	}

	void DisplayTeam();
};

