// Fill out your copyright notice in the Description page of Project Settings.

#include "TwitchTest.h"
#include "CommandRegistry.h"

// ===== Commands =====

template<class CMD = FCommand>
void FCommandRegistry<CMD>::Register(CMD* command)
{
	//if (!CMD::Execute) return;

	// Add command to list
	Commands.Add(command->GetName(), command);
}

template<class CMD = FCommand>
CMD* FCommandRegistry<CMD>::Get(FString name)
{
	// Check if command exists
	if (!IsCommand(name)) return NULL;

	// Get command from list
	return Commands[name];
}

template<class CMD = FCommand>
bool FCommandRegistry<CMD>::Execute(FString name)
{
	CMD* command = Get(name);

	// Execute command
	if (command)
	{
		command->Execute();
		return true;
	}

	// Command not found
	return false;
}

template<class CMD = FCommand>
bool FCommandRegistry<CMD>::IsCommand(FString name)
{
	return Commands.Contains(name);
}

template<class CMD = FCommand>
FCommandRegistry<CMD>::~FCommandRegistry()
{
	// Free registered commands
	for (auto& cmd : Commands)
		delete (cmd.Value);
}
