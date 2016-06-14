
#pragma once

#include "TwitchPlaysAPI.h"
#include "CommandRegistry.h"

// Declare static variables
TSet<FString> FCommandRegistry::ExistingKeywords;

/**
* Registers a command.
*/
void FCommandRegistry::Register(FCommand* command)
{
	// Add keyword to list
	ExistingKeywords.Add(command->GetName());

	// Add command to list
	Commands.Add(command->GetName(), command);
}

/**
* Gets a command.
*/
FCommand* FCommandRegistry::Get(FString name)
{
	// Check if command exists
	if (!IsCommand(name)) return NULL;

	// Get command from list
	return Commands[name];
}

/**
* Executes a command.
*/
bool FCommandRegistry::Execute(FCommandParser parser)
{
	FCommand* command = Get(parser.GetName());

	// Execute command
	if (command)
	{
		command->Execute(parser);
		return true;
	}

	// Command not found
	return false;
}

/**
* Checks if it is a command.
*/
bool FCommandRegistry::IsCommand(FString name)
{
	return Commands.Contains(name);
}

/**
* Free all commands.
*/
FCommandRegistry::~FCommandRegistry()
{
	// Free registered commands
	for (auto& cmd : Commands)
		delete (cmd.Value);
}
