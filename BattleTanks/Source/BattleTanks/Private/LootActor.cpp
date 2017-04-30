

#include "BattleTanks.h"
#include "Item/Item.h"
#include "TankGameInstance.h"
#include "Item/ItemManager.h"
#include "Model/ModelManager.h"
#include "Model/JsonModel.h"
#include "Tank.h"
#include "LootActor.h"


// Sets default values
ALootActor::ALootActor()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	CollisionBox = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Collision Box"));
	SetRootComponent(CollisionBox);
	CollisionBox->bGenerateOverlapEvents = false;
	CollisionBox->SetVisibility(false);
	CollisionBox->SetCollisionProfileName(TEXT("Custom"));
	CollisionBox->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	CollisionBox->SetCollisionObjectType(ECollisionChannel::ECC_PhysicsBody);
	CollisionBox->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Overlap);

	RotatingComponent = CreateDefaultSubobject<URotatingMovementComponent>(TEXT("RotatingComponent"));
	RotatingComponent->RotationRate = FRotator(0, 45, 0);

	static ConstructorHelpers::FObjectFinder<UStaticMesh> Cube(TEXT("StaticMesh'/Engine/BasicShapes/Cube.Cube'")); // Finds cube static mesh and sets it to TouchControllerAsset

	if (Cube.Succeeded())
	{
		CollisionBox->SetStaticMesh(Cube.Object);
	}

	CollisionBox->OnComponentBeginOverlap.AddDynamic(this, &ALootActor::OnOverlapBegin);
}

void ALootActor::SetItem(UItem* ItemToSet)
{
	if(!ItemToSet)
		Destroy();

	Item = ItemToSet;
	UTankGameInstance* GameInstance = Cast<UTankGameInstance>(GetWorld()->GetGameInstance());
	if (GameInstance)
	{
		UModelManager* ModelManager = GameInstance->GetModelManager();
		UItemManager* ItemManager = GameInstance->GetItemManager();

		FString ItemName = ItemManager->GetItemName(Item);
		UJsonModel* Model = ModelManager->GetModel(ItemName);
		Model->AttachToActor(this);
	}

}

void ALootActor::OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	ATank* Tank = Cast<ATank>(OtherActor);
	if (Tank)
	{
		Item->OnCollide(Tank);
		Destroy();
	}
}


// Called when the game starts or when spawned
void ALootActor::BeginPlay()
{
	Super::BeginPlay();
	CollisionBox->bGenerateOverlapEvents = true;
}

// Called every frame
void ALootActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	float Speed = 2.f;
	float Height = 20.f;

	FVector NewLocation = GetActorLocation();
	float DeltaHeight = (FMath::Sin((RunningTime + DeltaTime) * Speed) - FMath::Sin(RunningTime * Speed));
	NewLocation.Z += DeltaHeight * Height;
	RunningTime += DeltaTime;
	SetActorLocation(NewLocation);
}

