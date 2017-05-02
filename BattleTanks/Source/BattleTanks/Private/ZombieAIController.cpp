

#include "BattleTanks.h"
#include "ZombieAIController.h"

void AZombieAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	auto PlayerTank = GetWorld()->GetFirstPlayerController()->GetPawn();

	if (!ensure(PlayerTank))
	{
		return;
	}

	// Move towards the player
	MoveToActor(PlayerTank, 200);
}


