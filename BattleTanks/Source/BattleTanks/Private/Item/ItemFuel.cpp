

#include "BattleTanks.h"
#include "ItemFuel.h"


void UItemFuel::OnCollide(ATank* Actor)
{
	//BlueprintImplementableEvent
	Actor->AddFuel(Amount);
}