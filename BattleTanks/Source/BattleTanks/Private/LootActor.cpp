

#include "BattleTanks.h"
#include "Item/Item.h"
#include "LootActor.h"


// Sets default values
ALootActor::ALootActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));

	RotatingComponent = CreateDefaultSubobject<URotatingMovementComponent>(TEXT("RotatingComponent"));
	RotatingComponent->RotationRate = FRotator(0, 45,0);

}

void ALootActor::SetItem(UItem* ItemToSet)
{
	ALootActor* LootActor = this;
	ItemToSet->OnLootActorSet(LootActor);

}


// Called when the game starts or when spawned
void ALootActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ALootActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

