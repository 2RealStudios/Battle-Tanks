

#pragma once

#include "GameFramework/Pawn.h"
#include "MainMenuCharacter.generated.h"

class UMotionControllerComponent;

UCLASS()
class BATTLETANKS_API AMainMenuCharacter : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AMainMenuCharacter();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;

private:
	UPROPERTY(EditAnywhere)
	UCameraComponent* HMDCamera;

	UPROPERTY(EditAnywhere)
	UCapsuleComponent* CollisionCapsule;

	UPROPERTY(EditAnywhere)
	USceneComponent* Scene;

	UPROPERTY(EditAnywhere)
	UMotionControllerComponent* LeftHandController;

	UPROPERTY(EditAnywhere)
	UMotionControllerComponent* RightHandController;

	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* LeftHandMesh;

	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* RightHandMesh;
	
};
