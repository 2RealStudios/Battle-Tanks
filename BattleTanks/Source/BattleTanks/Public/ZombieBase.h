

#pragma once

#include "GameFramework/Character.h"
#include "ZombieBase.generated.h"

UCLASS()
class BATTLETANKS_API AZombieBase : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AZombieBase();
	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const & DamageEvent, class AController * EventInstigator, AActor * DamageCauser) override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION(BlueprintCallable, meta = (Animation))
	float GetTransitionAnimationSpeed();

	UFUNCTION(BlueprintCallable, meta = (Animation))
	float GetSpeed();

	UPROPERTY(EditAnywhere, meta = (Test))
	float TransitionAnimationSpeed = 10.0f; // Determines what speed the idle/run animation switches at

	UPROPERTY(BlueprintReadOnly, EditAnywhere, meta = (Test))

	float DistanceToHitTank = 210.0f;

	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit);
	
	void DropItem();

};
