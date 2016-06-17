// Fill out your copyright notice in the Description page of Project Settings.

#include "TwitchPlaysAPI.h"
#include "BallCommands.h"

#define Val 4

/**
 * Command moving ball to the left.
 */
void FBallLeftCommand::Execute(FCommandParser parser)
{
	// Move ball to the left
	const FVector Torque = FVector(-1.f * Val * 500000.0f, 0.f, 0.f);
	(Ball->GetOurVisibleComponent())->AddTorque(Torque);
}

/**
 * Command moving ball to the right.
 */
void FBallRightCommand::Execute(FCommandParser parser)
{
	// Move ball to the right
	const FVector Torque = FVector(1.f * Val * 500000.0f, 0.f, 0.f);
	(Ball->GetOurVisibleComponent())->AddTorque(Torque);
}

/**
  * Command moving ball to Forward.
  */
void FBallForwardCommand::Execute(FCommandParser parser)
{
	// Move ball to Forward
	const FVector Torque = FVector(0.f, -1.f * Val * 500000.0f, 0.f);
	(Ball->GetOurVisibleComponent())->AddTorque(Torque);
}

/**
  * Command moving ball to Backward.
  */
void FBallBackwardCommand::Execute(FCommandParser parser)
{
	// Move ball to Backward
	const FVector Torque = FVector(0.f, 1.f * Val * 500000.0f, 0.f);
	(Ball->GetOurVisibleComponent())->AddTorque(Torque);
}

/**
  * Command jump.
  */
void FBallJumpCommand::Execute(FCommandParser parser)
{
	//jump
	const FVector Impulse = FVector(0.f, 0.f, 9000.0f);
	(Ball->GetOurVisibleComponent())->AddImpulse(Impulse);
}
