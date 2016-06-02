// Fill out your copyright notice in the Description page of Project Settings.

#include "TwitchTest.h"
#include "BallCommands.h"

#define Val 4

/**
 * Command moving ball to the left.
 */
void FBallLeftCommand::Execute()
{
	// Move ball to the left
	//FVector velocity = Ball->GetCurrentVelocity();
	//velocity.X = FMath::Clamp(-1.0f, -1.0f, 1.0f) * 100.0f;
	//Ball->SetCurrentVelocity(velocity);

	const FVector Torque = FVector(-1.f * Val * 500000.0f, 0.f, 0.f);
	(Ball->GetOurVisibleComponent())->AddTorque(Torque);
}

/**
 * Command moving ball to the right.
 */
void FBallRightCommand::Execute()
{
	// Move ball to the right
	//FVector velocity = Ball->GetCurrentVelocity();
	//velocity.X = FMath::Clamp(1.0f, -1.0f, 1.0f) * 100.0f;
	//Ball->SetCurrentVelocity(velocity);

	const FVector Torque = FVector(1.f * Val * 500000.0f, 0.f, 0.f);
	(Ball->GetOurVisibleComponent())->AddTorque(Torque);
}

/**
* Command moving ball to Forward.
*/
void FBallForwardCommand::Execute()
{
	// Move ball to Forward
	const FVector Torque = FVector(0.f, -1.f * Val * 500000.0f, 0.f);
	(Ball->GetOurVisibleComponent())->AddTorque(Torque);
}

/**
* Command moving ball to Backward.
*/
void FBallBackwardCommand::Execute()
{
	// Move ball to Backward
	const FVector Torque = FVector(0.f, 1.f * Val * 500000.0f, 0.f);
	(Ball->GetOurVisibleComponent())->AddTorque(Torque);
}