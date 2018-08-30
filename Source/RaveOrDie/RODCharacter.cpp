// Fill out your copyright notice in the Description page of Project Settings.

#include "RODCharacter.h"
#include "UObject/ConstructorHelpers.h"
#include "Camera/CameraComponent.h"
#include "Components/DecalComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/SpringArmComponent.h"
#include "Materials/Material.h"
#include "Engine.h"
#include "Engine/World.h"
#include "HUDManager.h"
#include "RODPlayerController.h"

// Sets default values
ARODCharacter::ARODCharacter()
{

	// Set size for player capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	// Don't rotate character to camera direction
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Rotate character to moving direction
	GetCharacterMovement()->RotationRate = FRotator(0.f, 640.f, 0.f);
	GetCharacterMovement()->bConstrainToPlane = true;
	GetCharacterMovement()->bSnapToPlaneAtStart = true;

	// Create a camera boom...
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->bAbsoluteRotation = true; // Don't want arm to rotate when character does
	CameraBoom->TargetArmLength = 600.f;
	CameraBoom->RelativeRotation = FRotator(-60.f, 0.f, 0.f);
	CameraBoom->bDoCollisionTest = false; // Don't want to pull camera in when it collides with level

	OnActorHit.AddDynamic(this, &ARODCharacter::OnHit);
										  // Create a camera...
	TopDownCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("TopDownCamera"));
	TopDownCameraComponent->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	TopDownCameraComponent->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

	// Activate ticking in order to update the cursor every frame.
	PrimaryActorTick.bCanEverTick = false;
	PrimaryActorTick.bStartWithTickEnabled = false;

	bCanAttack = true;
	bIsInMeleeAttack = false;
	GunEquipped = false;

	Seconds = 0;
	Minutes = 0;
	Hours = 0;

	LIFE=MAXLIFE = 100.f;

}

// Called when the game starts or when spawned
void ARODCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	GetWorld()->GetTimerManager().SetTimer(ClockTimer, this, &ARODCharacter::Clock, 1.0f);
	HUDManager=GetWorld()->SpawnActor<AHUDManager>();
	InitializeHUDValues();
}

void ARODCharacter::InitializeHUDValues()
{
	HUDManager->UpdateTime(Hours, Minutes, Seconds);
	HUDManager->FinishBossFight();
	HUDManager->UpdateLife(MAXLIFE, LIFE);
	HUDManager->TurnToMelee();
	//HUDManager->UpdateAmo();
}

void ARODCharacter::OnHit(AActor* SelfActor, AActor* OtherActor, FVector NormalImpulse, const FHitResult& Hit) {

	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, TEXT("Me ha golpeado el enemigo"));


}

void ARODCharacter::Clock()
{
	if (++Seconds >= 60)
	{
		Seconds = 0;
		
		if (++Minutes >= 60)
		{
			Minutes = 0;
			Hours++;
		}
	}

	HUDManager->UpdateTime(Hours, Minutes, Seconds);
}

void ARODCharacter::Attack()
{
	if (GunEquipped)
	{
		DistanceAttack();
	}
	else
	{
		MeleeAttack();
	}
}

void ARODCharacter::SwapWeapon()
{
	GunEquipped = !GunEquipped;

	if (GunEquipped)
	{
		HUDManager->TurnToGun();
	}
	else
	{
		HUDManager->TurnToMelee();
	}
}

float ARODCharacter::GetMeleeDamage() const
{
	return 0.f;
}

void ARODCharacter::MeleeAttack()
{
	bIsInMeleeAttack = true;

}

void ARODCharacter::DistanceAttack()
{

}

void ARODCharacter::FinishMeleeAttack()
{
	bCanAttack = true;
	bIsInMeleeAttack = false;
}

void ARODCharacter::FinishDistanceAttack()
{
	bCanAttack = true;
}
