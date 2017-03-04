

#pragma once

#include "GameFramework/Actor.h"
#include "LootActor.generated.h"

class UItem;

UCLASS()
class BATTLETANKS_API ALootActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ALootActor();

	//UStaticMeshComponent* Mesh;

	// ??? GetItem();
	void SetItem(UItem* ItemToSet);
	URotatingMovementComponent* RotatingComponent;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	UItem* Item;
	float RunningTime;
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	
	
};
