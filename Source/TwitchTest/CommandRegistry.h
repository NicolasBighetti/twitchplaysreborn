// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "WorldCommand.h"

/**
 * 
 */
template<class CMD = FCommand>
class TWITCHTEST_API FCommandRegistry
{
private:
	// Commands list
	TMap<FString, CMD*> Commands;
public:
	// World commands
	static const FCommandRegistry<FWorldCommand> World;

	// === Commands management

	/**
	  * Registers a command.
	  */
	void Register(CMD* command) {
		// Add command to list
		Commands.Add(command->GetName(), command);
	}

	/**
	  * Gets a command.
	  */
	CMD* Get(FString name)
	{
		// Check if command exists
		if (!IsCommand(name)) return NULL;

		// Get command from list
		return Commands[name];
	}

	/**
	  * Executes a command.
	  */
	bool Execute(FString name)
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

	/**
	  * Checks if it is a command.
	  */
	bool IsCommand(FString name)
	{
		return Commands.Contains(name);
	}

	/**
	  * Free all commands.
	  */
	~FCommandRegistry()
	{
		// Free registered commands
		for (auto& cmd : Commands)
			delete (cmd.Value);
	}
};
