// Fill out your copyright notice in the Description page of Project Settings.

#include "TwitchTest.h"
#include "Strategy.h"


Strategy::Strategy(BlockingQueue<FString>* q, TMap<FString, FString>* m) {

	queue = q;
	Messages = m;

}

void Strategy::Receive(FString userName, FString message) {
	Messages->Add(userName, message);
	queue->push(message);
}

void Strategy::OnTick() {}
