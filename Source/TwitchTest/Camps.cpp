// Fill out your copyright notice in the Description page of Project Settings.

#include "TwitchTest.h"
#include "Camps.h"

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
	int res = Pseudo.Remove(pseudo);
	if (res != 0)
		TotalPlayer--;

	return res;
}

bool Camps::IsInTeam(FString pseudo) {
	return Pseudo.Contains(pseudo);
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