// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/StaticMeshComponent.h"
#include "TankTrack.generated.h"

/**
* TankTrack is used to set maxmim driving force, and to apply force to the tank.
*/
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class BATTLETANKS_API UTankTrack : public UStaticMeshComponent
{
	GENERATED_BODY()
	
public:

	// Sets a throttle between -1 and +1
	UFUNCTION(BluePrintCallable, Category = Input)
	void SetThrottle(float Throttle);
	
	// TODO clamp actual throttle value so player can't over-drive
};
