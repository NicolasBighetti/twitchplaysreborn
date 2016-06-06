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
	//void SetKeyword(Commande keyword);
	void SetPseudo(FString pseudo);
	/*
	void SetCommande(Commande commande);
	Commande GetCommandByKeyword(FString keyword);
	void ExecuteCommand(FString keyword);
	*/
	bool IsInTeam(FString pseudo);

private:

	// TArray<Commande> Keyword;
	TArray<FString> Pseudo;
	uint32 Total_player;
	//Commande commande;
};

