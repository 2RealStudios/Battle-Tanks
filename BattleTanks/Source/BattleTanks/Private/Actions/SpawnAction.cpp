

#include "BattleTanks.h"
#include "LootActor.h"
#include "Item/Item.h"
#include "Actions/SpawnAction.h"



void USpawnAction::doAction(AActor* ActorCalling)
{
	UWorld* World = ActorCalling->GetWorld();
	auto LootActor = World->SpawnActor<ALootActor>(ALootActor::StaticClass(), ActorCalling->GetActorLocation(), ActorCalling->GetActorRotation());
	LootActor->SetItem(NewObject<UItem>());
	//TODO MAKE UITEM
	// Ammo 1 : 5 : 10 : 20
}

