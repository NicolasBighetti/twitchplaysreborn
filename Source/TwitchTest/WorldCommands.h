// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "WorldCommand.h"

/**
* Join command.
*/
class TWITCHTEST_API FJoinWorldCommand : public FWorldCommand {
	virtual void Execute(FCommandParser parser);
};
