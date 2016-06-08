// Fill out your copyright notice in the Description page of Project Settings.

#include "TwitchTest.h"
#include "Anarchy.h"


void Anarchy::OnTick() {

	UE_LOG(LogTemp, Warning, TEXT("Anarchy OnTick"));

	auto It = Messages->CreateConstIterator();

	if (It) {
		queue->push(*It.Value());
		Messages->Empty();
	}
}

void Anarchy::Receive(FString userName, FString message) {

	Messages->Add(userName, message);
}
