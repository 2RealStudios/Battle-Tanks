

#include "BattleTanks.h"
#include "Action.h"
#include "Actions/SpawnAction.h"
#include "ActionManager.h"

bool UActionManager::AddActions()
{
	UE_LOG(LogTemp, Warning, TEXT("Adding Actions"))

	try
	{
		AddEmpty();

		auto SpawnActor = NewObject<USpawnAction>();
		Actions.Add(FString("fuel"), SpawnActor);
		Actions.Add(FString("ammo"), SpawnActor);


	}
	catch (const std::exception&)
	{
		UE_LOG(LogTemp, Warning, TEXT("Didn't work"))
		return false;
	}
	return true;
}

UAction* UActionManager::GetAction(FString ActionName)
{
	if (Actions.Contains(ActionName))
	{
		return Actions[ActionName];
	}
	UE_LOG(LogTemp, Warning, TEXT("UAction for %s not found defaulting to EMPTY"), *ActionName)

	return EMPTY;

}

UAction* UActionManager::GetEmpty()
{
	return EMPTY;
}

void UActionManager::AddEmpty()
{
	EMPTY = NewObject<UAction>();
	Actions.Add(FString("empty"), EMPTY);
}
