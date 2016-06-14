// Fill out your copyright notice in the Description page of Project Settings.

#include "TwitchPlaysAPI.h"
#include "WorldCommands.h"

#define Val 4

/**
 * Join command.
 */
void FJoinWorldCommand::Execute(FCommandParser parser)
{
	// Add player to team
	Context->GetCamps()->AddPlayer(
		parser.GetUserName(), // Username
		//CampsManager::AUTO_STRICT, // Auto-balance
		CampsManager::MANUAL, //Without Auto-balance
		parser.NextInt() // Camp ID
	);
}