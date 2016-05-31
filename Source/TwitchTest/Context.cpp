// Fill out your copyright notice in the Description page of Project Settings.
#include "TwitchTest.h"
#include "Context.h"


Context::Context(uint32 nb) {
	TArray<Camps> ListCamps;
}


TArray<Camps> Context::GetListCamps()
{
	return TArray<Camps>();
}

void Context::AddCamps(Camps camps) {
	ListCamps.Add(camps);
}
