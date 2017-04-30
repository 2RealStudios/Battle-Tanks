

#include "BattleTanks.h"
#include "TankGameInstance.h"
#include "LootManager.h"
#include "Action.h"
#include "Tank.h"
#include "ZombieBase.h"


// Sets default values
AZombieBase::AZombieBase()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	this->GetCapsuleComponent()->SetNotifyRigidBodyCollision(true);
	this->GetCapsuleComponent()->OnComponentHit.AddDynamic(this, &AZombieBase::OnHit);

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
	DropItem();
	return DamageAmount;
}

void AZombieBase::DropItem()
{
	UTankGameInstance* GameInstance = Cast<UTankGameInstance>(GetGameInstance());
	if (GameInstance)
	{
		UE_LOG(LogTemp, Warning, TEXT("Drop Item"))
		auto LootManager = GameInstance->GetLootManager();
		auto Action = LootManager->GetLoot(FString("zombie1"));
		Action->doAction(this);
	}
	Destroy();
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


void AZombieBase::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit)
{
	ATank* Tank = Cast<ATank>(OtherActor);
	if (Tank)
	{
		if(Tank->GetVelocity().Size() > 0)
		{
			Destroy();
		}
	}
}
