

#include "BattleTanks.h"
#include "LootActor.h"
#include "Item.h"


void UItem::OnLootActorSet(ALootActor* LootActor)
{

	UStaticMeshComponent* Mesh = NewObject<UStaticMeshComponent>(LootActor);
	if (Mesh)
	{
		Mesh->RegisterComponent();
		Mesh->AttachToComponent(LootActor->GetRootComponent(), FAttachmentTransformRules::KeepRelativeTransform);
	}

	UE_LOG(LogTemp, Warning, TEXT("Finding Mesh"));
	UStaticMesh* ItemMesh = LoadObjFromPath<UStaticMesh>(TEXT("Static Mesh'/Game/StarterContent/Shapes/Shape_Cube.Shape_Cube'")); // Finds cube static mesh and sets it to CubeVisualAsset

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
