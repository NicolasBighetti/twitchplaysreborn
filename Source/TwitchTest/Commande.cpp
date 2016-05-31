// Fill out your copyright notice in the Description page of Project Settings.

#include "TwitchTest.h"
#include "Commande.h"

Commande::Commande(FString cmd, void (*fct)()) {

	Cmd = cmd;
	Fct = fct;
}

