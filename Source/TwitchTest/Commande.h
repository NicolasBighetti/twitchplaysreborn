// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

/**
 * 
 */
class TWITCHTEST_API Commande
{
public:

	Commande(FString Cmd, void(*fct)());

private:

	FString Cmd;
	void *Fct;

};
