

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

	auto ItemMesh = GetStaticMesh(TEXT("/Engine/BasicShapes/Cube.Cube")); // Finds cube static mesh

	auto MaterialPath = Format(FString("/Game/Item/M_Item{0}.M_Item{0}"), FString::FromInt(Amount));

	auto Material = GetMaterial(MaterialPath); // Finds item material
	
	if (ItemMesh)
	{
		UE_LOG(LogTemp, Warning, TEXT("Setting Mesh"));
		Mesh->SetStaticMesh(ItemMesh);
		Mesh->SetWorldScale3D(FVector(1));
		if (Material)
		{
			Mesh->SetMaterial(0, Material);
		}
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Unable to find cube?"));
	}
}



