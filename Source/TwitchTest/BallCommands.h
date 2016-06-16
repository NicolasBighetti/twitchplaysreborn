// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Command.h"
#include "Ball.h"

/**
* Ball command.
*/
class FBallCommand : public FCommand
{
protected:
	ABall* Ball;
public:
	FBallCommand(FString _name, ABall* _ball) : FCommand(_name), Ball(_ball) {}
};

/**
 * Command moving ball to the left.
 */
class FBallLeftCommand : public FBallCommand
{
public:
	FBallLeftCommand(ABall* _ball) : FBallCommand(TEXT("q"), _ball) {}
	virtual void Execute(FCommandParser parser);
};

/**
 * Command moving ball to the right.
 */
class FBallRightCommand : public FBallCommand
{
public:
	FBallRightCommand(ABall* _ball) : FBallCommand(TEXT("d"), _ball) {}
	virtual void Execute(FCommandParser parser);
};

/**
* Command moving ball Forward.
*/
class FBallForwardCommand : public FBallCommand
{
public:
	FBallForwardCommand(ABall* _ball) : FBallCommand(TEXT("z"), _ball) {}
	virtual void Execute(FCommandParser parser);
};

/**
* Command moving ball backward.
*/
class FBallBackwardCommand : public FBallCommand
{
public:
	FBallBackwardCommand(ABall* _ball) : FBallCommand(TEXT("s"), _ball) {}
	virtual void Execute(FCommandParser parser);
};


class FBallJumpCommand : public FBallCommand
{
public:
	FBallJumpCommand(ABall* _ball) : FBallCommand(TEXT("a"), _ball) {}
	virtual void Execute(FCommandParser parser);
};
