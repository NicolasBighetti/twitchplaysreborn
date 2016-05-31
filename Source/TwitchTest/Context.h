// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Camps.h"

/**
 * 
 */
class TWITCHTEST_API Context
{
public:

	Context(uint32 nb);
	TArray<Camps> GetListCamps();
	void AddCamps(Camps camps);

private:

	TArray<Camps> ListCamps;
};

