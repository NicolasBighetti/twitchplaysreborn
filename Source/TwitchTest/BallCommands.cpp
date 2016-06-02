// Fill out your copyright notice in the Description page of Project Settings.

#include "TwitchTest.h"
#include "BallCommands.h"

/**
 * Command moving ball to the left.
 */
void FBallLeftCommand::Execute()
{
	// Move ball to the left
	FVector velocity = Ball->GetCurrentVelocity();
	velocity.X = FMath::Clamp(-1.0f, -1.0f, 1.0f) * 100.0f;
	Ball->SetCurrentVelocity(velocity);
}

/**
 * Command moving ball to the right.
 */
void FBallRightCommand::Execute()
{
	// Move ball to the right
	FVector velocity = Ball->GetCurrentVelocity();
	velocity.X = FMath::Clamp(1.0f, -1.0f, 1.0f) * 100.0f;
	Ball->SetCurrentVelocity(velocity);
}