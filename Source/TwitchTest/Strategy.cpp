// Fill out your copyright notice in the Description page of Project Settings.

#include "TwitchTest.h"
#include "Strategy.h"


Strategy::Strategy(BlockingQueue<FString>* q, CampsManager* campsmanager) {

	queue = q;
	camps = campsmanager;
	int i;
	int nb = camps->GetNbCamps();

	UE_LOG(LogTemp, Warning, TEXT("multi camps test %d"), nb);

	if (nb <= 1) {
		multicamps = false;
	}
	else
		multicamps = true;

	for (i = 0; i < nb; i++)
		Messages.Add(TMap<FString, FString>());
}

void Strategy::Receive(FString userName, FString message) {
	int cmp = 1;
	multicamps = true;

	if (multicamps) {
		cmp = camps->GetCampByPseudo(userName);
		UE_LOG(LogTemp, Warning, TEXT("multi camps test %d"), cmp);
	}
	if (cmp > 0) {
		UE_LOG(LogTemp, Warning, TEXT("test dans strategy receive %d"), cmp);
		Messages[cmp-1].Add(userName, message);
		camps->getCamps(cmp)->GetQueue()->push(message);
		//queue->push(message);
	}
}

void Strategy::OnTick() {}
