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
#include "RODGameStateBase.h"
#include "Subject.h"
#include "GameManager.h"
#include "Evento.h"
#include "Bullet.h"
#include "PlayerBullet.h"
#include "EnemyBullet.h"


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

	// Create a gun mesh component
	FP_Gun = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("FP_Gun"));
	FP_Gun->SetOnlyOwnerSee(true);			// only the owning player will see this mesh
	FP_Gun->bCastDynamicShadow = false;
	FP_Gun->CastShadow = false;
	FP_Gun->SetupAttachment(RootComponent);
	FP_Gun->SetRelativeLocation(FVector(40.f, 10.f, 50.f));
	FP_Gun->SetRelativeRotation(FRotator(0.f, 0.f, -90.f));

	// Default offset from the character location for projectiles to spawn
	GunOffset = FVector(130.0f, 0.0f, 50.0f);

	OnActorHit.AddDynamic(this, &ARODCharacter::OnHit);
										  // Create a camera...
	TopDownCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("TopDownCamera"));
	TopDownCameraComponent->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	TopDownCameraComponent->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

	// Activate ticking in order to update the cursor every frame.
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = true;

	bIsInMeleeAttack = false;
	GunEquipped = false;
	bInactivity = false;
	bReloading = false;
	bDead = false;
	bCanDistanceAttack = true;

	Time = FTimeStruct();

	LIFE=MAXLIFE = 100.f;

}

// Called when the game starts or when spawned
void ARODCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	RODCharacterSubject = NewObject<USubject>();
	RODCharacterSubject->AddObserver(Cast<ARODGameStateBase>(UGameplayStatics::GetGameState(GetWorld()))->GetGameManager());

	FP_Gun->SetVisibility(false);

	GetWorld()->GetTimerManager().SetTimer(ClockTimer, this, &ARODCharacter::Clock, 1.0f);
	HUDManager=GetWorld()->SpawnActor<AHUDManager>();
	InitializeHUDValues();
}

void ARODCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (GetVelocity().SizeSquared() != 0.f)
	{
		UpdateInactivity();
	}
	else
	{
	
		const ARODPlayerController* Controller = Cast<ARODPlayerController>(GetController());
		float rotation = Controller->CalcRotation();

		if (rotation != 0)
		{
			SetActorRotation(FQuat(FRotator(0.f, rotation, 0.f)+GetActorRotation()));
			UpdateInactivity();
		}
		
	}

}

void ARODCharacter::InitializeHUDValues()
{
	HUDManager->UpdateTime(Time);
	HUDManager->FinishBossFight();
	HUDManager->UpdateLife(MAXLIFE, LIFE);
	HUDManager->TurnToMelee();
	//HUDManager->UpdateAmo();
}

void ARODCharacter::OnHit(AActor* SelfActor, AActor* OtherActor, FVector NormalImpulse, const FHitResult& Hit) {
	
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, TEXT("Me ha golpeado el enemigo"));
	
	if (OtherActor->IsA(AEnemyBullet::StaticClass())) {
		AEnemyBullet* Bullet = Cast<AEnemyBullet>(OtherActor);
		UpdateLife(Bullet->GetDamage());

	}
	
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
	UpdateTime(&Time);
	HUDManager->UpdateTime(Time);
	GetWorld()->GetTimerManager().SetTimer(ClockTimer, this, &ARODCharacter::Clock, 1.0f);
}

void ARODCharacter::UpdateTime(FTimeStruct* Time)
{
	if (++(Time->Seconds) >= 60)
	{
		Time->Seconds = 0;

		if (++(Time->Minutes) >= 60)
		{
			Time->Minutes = 0;
			Time->Hours++;
		}
	}
}

void ARODCharacter::Attack()
{
	UpdateInactivity();

	if (GunEquipped)
	{
		if(bCanDistanceAttack) DistanceAttack();
	}
	else
	{
		if(!bIsInMeleeAttack) MeleeAttack();
	}	
}

void ARODCharacter::SwapWeapon()
{
	GunEquipped = !GunEquipped;
	UpdateInactivity();

	if (GunEquipped)
	{
		HUDManager->TurnToGun();
		FP_Gun->SetVisibility(true);
	}
	else
	{
		HUDManager->TurnToMelee();
		FP_Gun->SetVisibility(false);
	}
}

FTimeStruct ARODCharacter::GetPlayTime() const
{
	return Time;
}

float ARODCharacter::GetMeleeDamage() const
{
	return MeleeDamage;
}

void ARODCharacter::MeleeAttack()
{
	bIsInMeleeAttack = true;
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Purple, TEXT("atacando"));
	World->GetTimerManager().SetTimer(PunchingTimer, this, &ARODCharacter::FinishMeleeAttack, 1.f);
}

void ARODCharacter::DistanceAttack()
{
	World->GetTimerManager().SetTimer(ShotingTimer, this, &ARODCharacter::FinishDistanceAttack, 0.5f);
	
	const FRotator SpawnRotation = GetActorRotation();
	const FVector SpawnLocation =  GetActorLocation() + SpawnRotation.RotateVector(GunOffset);
	GetWorld()->SpawnActor<APlayerBullet>(SpawnLocation, SpawnRotation);
	RODCharacterSubject->Notify(this, EEvent::EVENT_SHOT);

}

/*************************************************************
	CAMBIAR CONDICIONES DE ATAQUE AL PLAYER CONTROLLER
	AQUI SOLO TENER LAS LLAMADAS
	
-*************************************************************/

void ARODCharacter::FinishMeleeAttack()
{
	bIsInMeleeAttack = false;
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, TEXT("He dejado de atacar"));
}

void ARODCharacter::FinishDistanceAttack()
{
	bCanDistanceAttack = true;
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

void ARODCharacter::UpdateLife(float Damage) {
	LIFE -= Damage;

	HUDManager->UpdateLife(MAXLIFE, LIFE);
	if (LIFE <= 0) {
		
		//FIN DEL JUEGO

	}
}