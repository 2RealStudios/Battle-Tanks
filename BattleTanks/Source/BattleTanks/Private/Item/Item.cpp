

#include "BattleTanks.h"
#include "LootActor.h"
#include "Item.h"


void UItem::OnLootActorSet(ALootActor* LootActor){}

UStaticMesh* UItem::GetStaticMesh(FName Path)
{
	return LoadObjFromPath<UStaticMesh>(Format(FString("Static Mesh'{0}'"), Path.ToString()));
}

UMaterial* UItem::GetMaterial(FName Path)
{
	return LoadObjFromPath<UMaterial>(Format(FString("Material'{0}'"), Path.ToString()));
}