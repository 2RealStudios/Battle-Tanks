// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTanks.h"
#include "TankTrack.h"
#include "TankMovementComponent.h"

void UTankMovementComponent::IntendMoveForward(float Throw)
{
	if (!LeftTrack || !RightTrack)
	{
		return;
	}
	//auto Time = GetWorld()->GetTimeSeconds();
	//UE_LOG(LogTemp, Warning, TEXT("Indend move forward throw: %f"), Throw);
	LeftTrack->SetThrottle(Throw);
	RightTrack->SetThrottle(Throw);
	// TODO prevent dual controll input

}

void UTankMovementComponent::IntendTurnRight(float Throw)
{
	if (!LeftTrack || !RightTrack)
	{
		return;
	}
	//auto Time = GetWorld()->GetTimeSeconds();
	//UE_LOG(LogTemp, Warning, TEXT("Indend move forward throw: %f"), Throw);
	LeftTrack->SetThrottle(Throw);
	RightTrack->SetThrottle(-Throw);
	// TODO prevent dual controll input

}

void UTankMovementComponent::Initialise(UTankTrack* LeftTrackToSet, UTankTrack* RightTrackToSet)
{
	
	LeftTrack = LeftTrackToSet;
	RightTrack = RightTrackToSet;

}



