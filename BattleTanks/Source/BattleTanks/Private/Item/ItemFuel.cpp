

#include "BattleTanks.h"
#include "LootActor.h"
#include "ItemFuel.h"

void UItemFuel::OnLootActorSet(ALootActor* LootActor)
{
	UE_LOG(LogTemp, Warning, TEXT("%d"), Amount)

	UStaticMeshComponent* Mesh = NewObject<UStaticMeshComponent>(LootActor);
	if (Mesh)
	{
		Mesh->RegisterComponent();
		Mesh->AttachToComponent(LootActor->GetRootComponent(), FAttachmentTransformRules::KeepRelativeTransform);
	}

	UE_LOG(LogTemp, Warning, TEXT("Finding Mesh"));

	auto ItemMesh = LoadObjFromPath<UStaticMesh>(TEXT("Static Mesh'/Engine/BasicShapes/Cube.Cube'")); // Finds cube static mesh and sets it to CubeVisualAsset
	
	if (ItemMesh)
	{
		UE_LOG(LogTemp, Warning, TEXT("Setting Mesh"));
		Mesh->SetStaticMesh(ItemMesh);
		Mesh->SetWorldScale3D(FVector(1));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Unable to find cube?"));
	}
}



