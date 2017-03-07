

#include "BattleTanks.h"
#include "LootActor.h"
#include "ItemAmmo.h"

void UItemAmmo::OnLootActorSet(ALootActor* LootActor)
{
	UStaticMeshComponent* Mesh = NewObject<UStaticMeshComponent>(LootActor);
	if (Mesh)
	{
		Mesh->RegisterComponent();
		Mesh->AttachToComponent(LootActor->GetRootComponent(), FAttachmentTransformRules::KeepRelativeTransform);
	}

	auto ItemMesh = GetStaticMesh(TEXT("/Engine/BasicShapes/Sphere.Sphere")); // Finds cube static mesh

	auto MaterialPath = Format(FString("/Game/Item/M_Item{0}.M_Item{0}"), FString::FromInt(Amount));

	auto Material = GetMaterial(MaterialPath); // Finds item material

	if (ItemMesh)
	{
		Mesh->SetStaticMesh(ItemMesh);
		Mesh->SetWorldScale3D(FVector(1));
		if (Material)
		{
			Mesh->SetMaterial(0, Material);
		}
	}
	else
	{
		//UE_LOG(LogTemp, Warning, TEXT("Unable to find cube?"));
	}
}


