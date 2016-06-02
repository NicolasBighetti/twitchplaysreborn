// Fill out your copyright notice in the Description page of Project Settings.

#include "TwitchTest.h"
#include "CommandRegistry.h"

void FCommandRegistry::Register(FCommand* command)
{
	// Add command to list
	Commands.Add(command->GetName(), command);
}

FCommand* FCommandRegistry::Get(FString name)
{
	// Check if command exists
	if (!Commands.Contains(name)) return NULL;

	// Get command from list
	return Commands[name];
}

bool FCommandRegistry::Execute(FString name)
{
	FCommand* command = Get(name);

	// Execute command
	if (command)
	{
		command->Execute();
		return true;
	}

	// Command not found
	return false;
}

FCommandRegistry::~FCommandRegistry()
{
	// Free registered commands
	for (auto& cmd : Commands)
		delete (cmd.Value);
}
