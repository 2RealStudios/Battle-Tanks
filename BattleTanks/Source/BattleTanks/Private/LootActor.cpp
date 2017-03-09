

#include "BattleTanks.h"
#include "Item/Item.h"
#include "TankGameInstance.h"
#include "Item/ItemManager.h"
#include "Model/ModelManager.h"
#include "Model/JsonModel.h"
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
	Item = ItemToSet;
	UTankGameInstance* GameInstance = Cast<UTankGameInstance>(GetWorld()->GetGameInstance());
	if (GameInstance)
	{
		UModelManager* ModelManager = GameInstance->GetModelManager();
		UItemManager* ItemManager = GameInstance->GetItemManager();

		FString ItemName = ItemManager->GetItemName(Item);
		UJsonModel* Model = ModelManager->GetModel(ItemName);
		Model->AttachToLootActor(this);
	}

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

