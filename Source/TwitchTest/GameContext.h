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

public:
	CampsManager* GetCamps() { return &Camps; }
};

