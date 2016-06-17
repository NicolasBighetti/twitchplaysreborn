// Fill out your copyright notice in the Description page of Project Settings.

#include "TwitchPlaysAPI.h"
#include "Camps.h"
#include "CoreMisc.h"

Camps::Camps(FString CampsName) {
	MessagesQueue = new TQueue<FString>();
	Queue = new BlockingQueue<FCommandParser>();
	Name = CampsName;
}

bool Camps::AddPlayer(FString pseudo) {
	// Check if player is not already in this camp
	if (!Pseudo.Contains(pseudo)) {
		Pseudo.Add(pseudo);
		TotalPlayer++;
		return true;
	}

	return false;
}

int Camps::RemovePlayer(FString pseudo)
{
	// Remove player from list
	int res = Pseudo.Remove(pseudo);

	// Check result
	if (res != 0)
		TotalPlayer--;

	return res;
}

bool Camps::IsInTeam(FString pseudo) {
	return Pseudo.Contains(pseudo);
}

void Camps::DisplayTeam()
{
	// Display every pseudos
	for (FString pseudo : Pseudo) {
		if (!pseudo.IsEmpty())
			UE_LOG(LogTemp, Warning, TEXT("%s"), *pseudo);
	}
}
