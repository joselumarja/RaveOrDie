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
#include "GameManager.h"
#include "RODPlayerController.h"

// Sets default values
ARODCharacter::ARODCharacter()
{
	World = GetWorld();
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
	CameraBoom->TargetArmLength = 500.f;
	CameraBoom->RelativeRotation = FRotator(-60.f, 0.f, 0.f);
	CameraBoom->bDoCollisionTest = false; // Don't want to pull camera in when it collides with level

	OnActorHit.AddDynamic(this, &ARODCharacter::OnHit);
										  // Create a camera...
	TopDownCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("TopDownCamera"));
	TopDownCameraComponent->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	TopDownCameraComponent->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

	// Activate ticking in order to update the cursor every frame.
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = true;

	bCanMeleeAttack = true;
	bIsInMeleeAttack = false;
	GunEquipped = false;
	bInactivity = false;
	bReloading = false;
	bDead = false;
	bCanAttack = true;

	Seconds = 0;
	Minutes = 0;
	Hours = 0;

	LIFE=MAXLIFE = 100.f;

}

// Called when the game starts or when spawned
void ARODCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	Manager = UGameManager::GetManager();
	Manager->InitializeGameManager();
	GetWorld()->GetTimerManager().SetTimer(ClockTimer, this, &ARODCharacter::Clock, 1.0f);
	HUDManager=GetWorld()->SpawnActor<AHUDManager>();
	InitializeHUDValues();
}

void ARODCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (GetVelocity().SizeSquared() != 0.f) UpdateInactivity();

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
	if (!bInvulnerability)
	{

		//if ((OtherActor != NULL) && (OtherActor->IsA(ALuchadoresAereosProjectile::StaticClass())) || (OtherActor->IsA(AEnemy::StaticClass())))
		//{

				//Manager->UpdateLives();
				//SetNormalShotState();
				//SetHitInvulnerability();
				//UGameplayStatics::PlaySoundAtLocation(this, HitSound, GetActorLocation());
			//UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ExplosionParticleSystem.Get(), GetActorLocation());
		//}
		//OtherActor->Destroy();
		bInvulnerability = true;
	}

}

void ARODCharacter::UpdateInactivity()
{
	bInactivity = false;
	GetWorld()->GetTimerManager().SetTimer(InactivityTimer, this, &ARODCharacter::SetInactivity, 6.0f);
}

void ARODCharacter::SetInactivity()
{
	bInactivity = true;
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
	GetWorld()->GetTimerManager().SetTimer(ClockTimer, this, &ARODCharacter::Clock, 1.0f);
}

void ARODCharacter::Attack()
{
	if (bCanAttack)
	{
		UpdateInactivity();

		if (GunEquipped)
		{
			DistanceAttack();
		}
		else
		{
			MeleeAttack();
		}
	}
	
}

void ARODCharacter::SwapWeapon()
{
	GunEquipped = !GunEquipped;
	UpdateInactivity();

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
	CanMeleeAttack = false;
	bIsInMeleeAttack = true;
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Purple, TEXT("atacando"));
	//World->GetTimerManager().SetTimer(TimerHandle_InvulnerabilityHitExpired, this, &ARODCharacter::AnimationExpired, 2.167f);
}

void ARODCharacter::DistanceAttack()
{
	//World->GetTimerManager().SetTimer(TimerHandle_InvulnerabilityHitExpired, this, &ARODCharacter::AnimationExpired, 1.167f)
	Manager->IncrementShots();

}

/*************************************************************
	CAMBIAR CONDICIONES DE ATAQUE AL PLAYER CONTROLLER
	AQUI SOLO TENER LAS LLAMADAS
	
-*************************************************************/

void ARODCharacter::FinishMeleeAttack()
{
	CanMeleeAttack = true;
	bIsInMeleeAttack = false;
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, TEXT("He dejado de atacar"));
}

void ARODCharacter::FinishDistanceAttack()
{
	bCanMeleeAttack = true;
}

void ARODCharacter::InvulnerabilityTimerExpired()
{
	bInvulnerability = false;
}

void ARODCharacter::SetHitInvulnerability()
{
	bInvulnerability = true;
	HitInvulnerabilityTime++;
	if (HitInvulnerabilityTime == 4.0) {
		bInvulnerability = false;
		HitInvulnerabilityTime = 0.0f;
		
	}
	else {
		
		//World->GetTimerManager().SetTimer(TimerHandle_InvulnerabilityHitExpired, this, &ARODCharacter::HitInvulnerabilityExpired, 0.5f);
	}
}

void ARODCharacter::HitInvulnerabilityExpired()
{
	//World->GetTimerManager().SetTimer(TimerHandle_InvulnerabilityHitExpired, this, &ARODCharacter::SetHitInvulnerability, 0.5f);
}

void ARODCharacter::SetInvulnerability()
{
	bInvulnerability = true;
	
	//UGameplayStatics::PlaySoundAtLocation(this, InvulnerabilitySound, GetActorLocation());
	//World->GetTimerManager().SetTimer(TimerHandle_InvulnerabilityExpired, this, &ARODCharacter::InvulnerabilityTimerExpired, InvulnerabilityTime);
}

