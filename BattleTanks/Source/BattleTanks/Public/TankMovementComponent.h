// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/NavMovementComponent.h"
#include "TankMovementComponent.generated.h"

class UTankTrack;

/**
 * Responsile for driving the tank tracks
 */
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class BATTLETANKS_API UTankMovementComponent : public UNavMovementComponent
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable, Category = "Setup")
	void Initialise(UTankTrack* LeftTrackToSet, UTankTrack* RightTrackToSet);
	
	// 1 is moving forward, -1 is moving backwards
	UFUNCTION(BlueprintCallable, Category = "Input")
	void IntendMoveForward(float Throw);

	// 1 is turning right, -1 is turning left
	UFUNCTION(BlueprintCallable, Category = "Input")
	void IntendTurnRight(float Throw);

private:
	// Called from the pathfinding logic by the AI controllers
	virtual void RequestDirectMove(const FVector& MoveVelocity, bool bForceMaxSpeed) override;

	UTankTrack* LeftTrack = nullptr;

	UTankTrack* RightTrack = nullptr;

};
