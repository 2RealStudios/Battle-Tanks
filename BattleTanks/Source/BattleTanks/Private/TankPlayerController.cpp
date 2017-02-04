// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTanks.h"
#include "TankPlayerController.h"

void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();
	
	auto ControlledTank = GetControlledTank();
	if (!ControlledTank)
	{
		UE_LOG(LogTemp, Warning, TEXT("PlayerController not possesing a tank"));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("PlayerController possesing %s"), *(ControlledTank->GetName()));
	}
}

void ATankPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	AimTowardsCrosshair();
}

ATank* ATankPlayerController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}

void ATankPlayerController::AimTowardsCrosshair()
{
	if (!GetControlledTank())
	{
		return;
	}

	FVector HitLocation; // Outparameter
	if (GetSightRayHitLocation(HitLocation)) // Has "side-effect", is hoing to line trace
	{
		UE_LOG(LogTemp, Warning, TEXT("HitLocation: %s"), *HitLocation.ToString());
		// Get world location of linetrace through crosshair
		// If it hit the landscape
			// Tell controlled tankto aim at this point
	}
}

// Get world location of linetrace though crosshair, true of hits landscape
bool ATankPlayerController::GetSightRayHitLocation(FVector& HitLocation) const
{
	HitLocation = FVector(1.0);
	return true;

}



