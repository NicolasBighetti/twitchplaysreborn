
#pragma once

#include "WorldCommand.h"

/**
*
*/
class TWITCHTEST_API FCommandRegistry
{
private:
	// Commands list
	TMap<FString, FCommand*> Commands;

	// Global commands keywords
	static TSet<FString> ExistingKeywords;
public:
	// World commands registry
	static FCommandRegistry* World() {
		static FCommandRegistry world;
		return &world;
	}

	// Check if commands exists
	static bool ExistsCommand(FString name)
	{
		return ExistingKeywords.Contains(name);
	}

	static void PrintKeywords() {
		for (FString m : FCommandRegistry::ExistingKeywords) {
			UE_LOG(LogTemp, Warning, TEXT("commande: %s"), *m);
		}
	}

	// === Commands management

	/**
	* Registers a command.
	*/
	void Register(FCommand* command);

	/**
	* Gets a command.
	*/
	FCommand* Get(FString name);

	/**
	* Executes a command.
	*/
	bool Execute(FCommandParser parser);

	/**
	* Checks if it is a command.
	*/
	bool IsCommand(FString name);

	/**
	* Free all commands.
	*/
	~FCommandRegistry();
};
