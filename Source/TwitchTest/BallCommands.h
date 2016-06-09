// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Command.h"
#include "Ball.h"

/**
* Ball command.
*/
class TWITCHTEST_API FBallCommand : public FCommand
{
protected:
	ABall* Ball;
public:
	FBallCommand(FString _name, ABall* _ball) : FCommand(_name), Ball(_ball) {}
};

/**
 * Command moving ball to the left.
 */
class TWITCHTEST_API FBallLeftCommand : public FBallCommand
{
public:
	FBallLeftCommand(ABall* _ball) : FBallCommand(TEXT("q"), _ball) {}
	virtual void Execute(FCommandParser parser);
};

/**
 * Command moving ball to the right.
 */
class TWITCHTEST_API FBallRightCommand : public FBallCommand
{
public:
	FBallRightCommand(ABall* _ball) : FBallCommand(TEXT("d"), _ball) {}
	virtual void Execute(FCommandParser parser);
};

/**
* Command moving ball Forward.
*/
class TWITCHTEST_API FBallForwardCommand : public FBallCommand
{
public:
	FBallForwardCommand(ABall* _ball) : FBallCommand(TEXT("z"), _ball) {}
	virtual void Execute(FCommandParser parser);
};

/**
* Command moving ball backward.
*/
class TWITCHTEST_API FBallBackwardCommand : public FBallCommand
{
public:
	FBallBackwardCommand(ABall* _ball) : FBallCommand(TEXT("s"), _ball) {}
	virtual void Execute(FCommandParser parser);
};


class TWITCHTEST_API FBallJumpCommand : public FBallCommand
{
public:
	FBallJumpCommand(ABall* _ball) : FBallCommand(TEXT("a"), _ball) {}
	virtual void Execute(FCommandParser parser);
};
