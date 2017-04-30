

#pragma once

#include "GameFramework/Actor.h"
#include "LootActor.generated.h"

class UItem;
/*
 *	The Actor that represents any item in game
 */
UCLASS()
class BATTLETANKS_API ALootActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ALootActor();

	//UStaticMeshComponent* Mesh;

	// Used to set item and attach model
	void SetItem(UItem* ItemToSet);

	// Used to make the actor rotate in place
	URotatingMovementComponent* RotatingComponent;

	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* CollisionBox;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:

	// Used to handle item pickup
	UFUNCTION()
	void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	
	// The item this actor is representing
	UItem* Item;

	// How long has this actor been alive, used to make actor oscillate 
	float RunningTime;
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	
	
};
