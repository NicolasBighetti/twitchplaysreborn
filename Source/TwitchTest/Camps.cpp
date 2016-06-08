// Fill out your copyright notice in the Description page of Project Settings.

#include "TwitchTest.h"
#include "Camps.h"
#include "CoreMisc.h"

Camps::Camps()
{
	MessagesQueue = new TQueue<FString>();
	Queue = new BlockingQueue<FString>();
}

bool Camps::AddPlayer(FString pseudo) {

	if (!Pseudo.Contains(pseudo)) {
		Pseudo.Add(pseudo);
		TotalPlayer++;

		return true;
	}

	return false;
}

int Camps::RemovePlayer(FString pseudo)
{

	DisplayTeam();

	int res = Pseudo.Remove(pseudo);

	if (res != 0)
		TotalPlayer--;

	DisplayTeam();

	return res;
}

bool Camps::IsInTeam(FString pseudo) {
	return Pseudo.Contains(pseudo);
}

void Camps::DisplayTeam()
{
	for(FString pseudo : Pseudo)
		UE_LOG(LogTemp, Warning, TEXT("%s"), *pseudo);
}

/*
void Camps::SetKeyword(Commande keyword) {
Keyword.Add(keyword);
}

void Camps::SetCommande(Commande cmd) {
commande = cmd;
}
Commande Camps::GetCommandByKeyword(FString keyword)
{
	for (Commande c : this->Keyword)
	{
		if (c.GetKeyword().Equals(keyword, ESearchCase::IgnoreCase))
			return c;
	}

	return Commande("null", NULL);
}

void Camps::ExecuteCommand(FString keyword)
{
	(this->GetCommandByKeyword(keyword)).execute();
}
*/