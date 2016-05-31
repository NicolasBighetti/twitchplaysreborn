// Fill out your copyright notice in the Description page of Project Settings.

#include "TwitchTest.h"
#include "Camps.h"

void Camps::SetCommande(Commande cmd) {
	commande = cmd;
}

void Camps::SetKeyword(Commande keyword) {
	Keyword.Add(keyword);
}

void Camps::SetPseudo(FString pseudo) {
	Pseudo.Add(pseudo);
}