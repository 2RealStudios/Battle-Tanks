// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTanks.h"
#include "TankMovementComponent.h"

void UTankMovementComponent::IntendMoveForward(float Throw)
{
	//auto Time = GetWorld()->GetTimeSeconds();
	UE_LOG(LogTemp, Warning, TEXT("Indend move forward throw: %f"), Throw);

}



