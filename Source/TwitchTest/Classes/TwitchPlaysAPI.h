// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Engine.h"


// For tests
#define TWITCH_CHECK(test, errorMsg) \
	if(!(test)) { UE_LOG(LogTemp, Display, TEXT("TWITCHTEST Error: %s"), TEXT(errorMsg)); return false; }