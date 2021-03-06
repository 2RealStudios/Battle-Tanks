// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/ActorComponent.h"
#include "TankAimingComponent.generated.h"


class UTankBarrel; // Forward Declaration
class UTankTurret; // Forward Declaration
class AProjectile;

// Enum for aiming state
UENUM()
enum class EFiringState : uint8
{
	Reloading, 
	Aiming,
	Locked,
	OutOfAmmo
};

// Hlds barrel's properties and Elevate method
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class BATTLETANKS_API UTankAimingComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UTankAimingComponent();

	// Aim at location passed
	void AimAt(FVector HitLocation);

	// Initialise the aiming component
	UFUNCTION(BlueprintCallable, Category = "Setup")
	void Initialise(UTankBarrel* BarrelToSet, UTankTurret* TurretToSet);

	// Fire a round
	UFUNCTION(BlueprintCallable, Category = "Firing")
	void Fire(int32 RoundsLeft);

	EFiringState GetFiringState() const;
	
	UFUNCTION(BlueprintCallable, Category = "Firing")
	int32 GetRoundsLeft() const;

	UFUNCTION(BlueprintCallable, Category = "Trajectory")
	FVector GetStartLocation() const;

	UFUNCTION(BlueprintCallable, Category = "Trajectory")
	FVector GetInitialVelocity() const;

protected:
	UPROPERTY(BlueprintReadOnly, Category = "State")
	EFiringState FiringState = EFiringState::Reloading;

private:
	virtual void BeginPlay() override;

	virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction) override;

	UTankBarrel* Barrel = nullptr;

	UTankTurret* Turret = nullptr;

	void MoveBarrelTowards(FVector AimDirection);

	bool IsBarrelMoving();

	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	TSubclassOf<AProjectile> ProjectileBlueprint;

	UPROPERTY(EditDefaultsOnly, Category = "Firing")
	float LaunchSpeed = 8000;

	UPROPERTY(EditDefaultsOnly, Category = "Trajectory")
	FVector StartLocation = FVector(0);

	UPROPERTY(EditDefaultsOnly, Category = "Trajectory")
	FVector InitialVelocity = FVector(0);

	UPROPERTY(EditDefaultsOnly, Category = "Firing")
	float ReloadTimeInSeconds = 0.0f;

	UPROPERTY(EditDefaultsOnly, Category = "Firing")
	int32 RoundsLeft = 25;

	double LastFireTime = 0;

	FVector AimDirection;

};
