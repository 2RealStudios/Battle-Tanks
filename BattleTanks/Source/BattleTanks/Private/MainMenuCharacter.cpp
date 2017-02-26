

#include "BattleTanks.h"
#include "MainMenuCharacter.h"


// Sets default values
AMainMenuCharacter::AMainMenuCharacter()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Create a dummy root component (location, rotation, scale, collision primitive) for the sole purpose of attaching components to
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));

	// Capsule settings (capsule is used for basic collision)
	CollisionCapsule = CreateDefaultSubobject<UCapsuleComponent>(TEXT("CollisionCapsule"));
	CollisionCapsule->SetCapsuleHalfHeight(96.0f);
	CollisionCapsule->SetCapsuleRadius(16.0f);
	CollisionCapsule->SetupAttachment(RootComponent);
	
	// Camera settings
	HMDCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("HeadMountedDisplayCamera"));
	HMDCamera->SetRelativeLocation(FVector(0.0f, 0.0f, -110.0f));
	HMDCamera->SetupAttachment(RootComponent);

	// Scene settings (scene is used for location(?))
	Scene = CreateDefaultSubobject<USceneComponent>(TEXT("Scene"));
	Scene->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void AMainMenuCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMainMenuCharacter::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

// Called to bind functionality to input
void AMainMenuCharacter::SetupPlayerInputComponent(class UInputComponent* InputComponent)
{
	Super::SetupPlayerInputComponent(InputComponent);

}

