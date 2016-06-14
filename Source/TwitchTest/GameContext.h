// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CampsManager.h"

/**
 * 
 */
class TWITCHTEST_API GameContext
{
private:
	CampsManager Camps;
	int32 strategy;

public:
	CampsManager* GetCamps() { return &Camps; }
	int32 GetStrategy() { return strategy;  }
	void SetStrategy(int32 strat) {
		strategy = strat;
	}
};

