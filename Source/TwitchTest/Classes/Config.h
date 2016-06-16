// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

/**
 * 
 */
class Config
{
private:
	// Loaded configuration
	TMap<FString, FString> Conf;
	
public:
	// Load configuration from file
	static Config Load(FString file);

	// Get configuration
	FString Get(FString key);
	int32 GetInt(FString key);
	float GetFloat(FString key);
};
