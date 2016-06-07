// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

// #include "Commande.h"

using namespace std;

/**
 * 
 */
class TWITCHTEST_API Camps
{
public:

	bool AddPlayer(FString pseudo);

	int RemovePlayer(FString pseudo);
	bool IsInTeam(FString pseudo);

	uint32 GetTotalPlayer() {
		return TotalPlayer;
	}
	TArray<FString> GetPlayerList() {
		return Pseudo;
	}

private:

	TArray<FString> Pseudo;
	uint32 TotalPlayer;

	
};

