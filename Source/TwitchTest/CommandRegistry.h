
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
	// === Commands management

	/**
	* Registers a command.
	*/
	void Register(CMD* command) {
		// Add keyword to list
		FWorldCommandRegistry::ExistingKeywords()->Add(command->GetName());

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
	bool Execute(FCommandParser parser)
	{
		CMD* command = Get(parser.GetName());

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

class TWITCHTEST_API FWorldCommandRegistry : public FCommandRegistry<FWorldCommand> {
private:
	FWorldCommandRegistry() {};

public:
	static FWorldCommandRegistry* GetInstance()
	{
		static FWorldCommandRegistry instance;
		return &instance;
	}

	// === Global commands management

	// Check if commands exists
	static bool ExistsCommand(FString name)
	{
		return FWorldCommandRegistry::ExistingKeywords()->Contains(name);
	}

	static TSet<FString>* ExistingKeywords()
	{
		static TSet<FString> existingKeywords;
		return &existingKeywords;
	}
};