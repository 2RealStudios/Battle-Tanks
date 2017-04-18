

#include "BattleTanks.h"
#include "TankGameInstance.h"
#include "LootManager.h"
#include "Action.h"
#include "ZombieBase.h"


// Sets default values
AZombieBase::AZombieBase()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AZombieBase::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AZombieBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void AZombieBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

float AZombieBase::TakeDamage(float DamageAmount, struct FDamageEvent const & DamageEvent, class AController * EventInstigator, AActor * DamageCauser)
{
	UTankGameInstance* GameInstance = Cast<UTankGameInstance>(GetGameInstance());
	if (GameInstance)
	{
		auto LootManager = GameInstance->GetLootManager();
		auto Action = LootManager->GetLoot(FString("zombie1"));
		Action->doAction(this);
		Destroy();
	}
	return DamageAmount;
}

float AZombieBase::GetTransitionAnimationSpeed()
{
	return TransitionAnimationSpeed;
}

float AZombieBase::GetSpeed()
{
	auto Velocity = this->GetVelocity();
	float Speed = Velocity.Size();
	return Speed;	
}
