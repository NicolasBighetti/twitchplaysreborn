// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CampsManager.h"

/**
 * 
 */
class GameContext
{
private:
	CampsManager Camps;
	FRunnable *TwitchRunnable = NULL;
	int32 strategy = 0;
	FString Admin;

public:
	CampsManager* GetCamps() { return &Camps; }
	int32 GetStrategy() { return strategy;  }
	void SetStrategy(int32 strat) {
		strategy = strat;
	}
	void SetReceiver(FRunnable *_TwitchRunnable) {
		TwitchRunnable = _TwitchRunnable;
	}
	FRunnable *getReceiver() {
		return TwitchRunnable;
	}

	FString GetAdmin() {
		return Admin;
	}

	void SetAdmin(FString admin) {
		Admin = admin;
	}
};

