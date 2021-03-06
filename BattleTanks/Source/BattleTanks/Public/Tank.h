// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Pawn.h"
#include "Tank.generated.h" // Put new includes above 

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FTankDelegate);

// TODO rewrite to have Tank set self up
UCLASS()
class BATTLETANKS_API ATank : public APawn
{
	GENERATED_BODY()

public:

	// Tank take damage - is this even used?
	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const & DamageEvent, class AController * EventInstigator, AActor * DamageCauser) override;

	// Returns current health as a percentage of starting health, between 0 and 1
	UFUNCTION(BlueprintPure, Category = "Health")
	float GetHealthPercent() const;

	// Called when tank is killed
	FTankDelegate OnDeath;

	// Add fuel to tank
	UFUNCTION(BlueprintImplementableEvent, Category = "Gas")
	void AddFuel(float Amount);

	// Add ammo to tank
	UFUNCTION(BlueprintImplementableEvent, Category = "Ammo")
	void AddAmmo(int32 Amount);

private:
	// Tanks starting health
	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	int32 StartingHealth = 100;
	
	UPROPERTY(VisibleAnywhere, Category = "Health")
	int32 CurrentHealth; // Initialised in BeginPlay

	// Sets default values for this pawn's properties
	ATank();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;

};
