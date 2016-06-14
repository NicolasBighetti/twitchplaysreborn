// Fill out your copyright notice in the Description page of Project Settings.

#include "TwitchTest.h"
#include "Config.h"

Config Config::Load(FString file) {
	Config conf;
	TArray<FString> fileConfig;

	// Get full file path
	file = FPaths::GameDir() + file;

	// Load configuration from file
	if (!FFileHelper::LoadANSITextFileToStrings(*file, NULL, fileConfig))
		// Load failed
		return conf;

	// Parse every configuration
	int nbLines = fileConfig.Num();
	for (int i = 0; i < nbLines; i++) {
		TArray<FString> keyValue;
		fileConfig[i].ParseIntoArray(keyValue, TEXT(": "));

		// Invalid line, skip it
		if (keyValue.Num() != 2) continue;

		// Parse values
		FString key = keyValue[0].Trim().TrimTrailing();
		FString value = keyValue[1].Trim().TrimTrailing();

		// Add configuration to map
		// UE_LOG(LogTemp, Warning, TEXT("Config: '%s':'%s'"), *key, *value);
		conf.Conf.Add(key, value);
	}

	return conf;
}

// Get configuration

FString Config::Get(FString key) {
	return Conf[key];
}

int32 Config::GetInt(FString key) {
	return FCString::Atoi(*Get(key));
}

float Config::GetFloat(FString key) {
	return FCString::Atof(*Get(key));
}
