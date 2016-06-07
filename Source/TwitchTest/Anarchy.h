// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "Strategy.h"

/**
 * 
 */
//class TWITCHTEST_API Anarchy : public Strategy, public UObject
class TWITCHTEST_API Anarchy : public Strategy
{
public:
	 
	//Anarchy(FTimerManager* w, BlockingQueue<FString>* q) : Strategy(q), UObject() {
	Anarchy(UWorld* w, BlockingQueue<FString>* q) : Strategy(q) {
		world = w;
		//world->GetTimerManager().SetTimer(TimerHandle, this, &Anarchy::OnTick, 2, false);
	};

	FTimerHandle TimerHandle;
	UWorld* world;

	void Receive() override;
	void OnTick() override;

};
