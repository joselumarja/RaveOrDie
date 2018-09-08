// Fill out your copyright notice in the Description page of Project Settings.

#include "FinalBoss.h"
#include "BossAIController.h"
#include "Engine.h"
#include "BehaviorTree/BehaviorTree.h"
#include "Perception/PawnSensingComponent.h"
#include "GameManager.h"
#include "Bullet.h"
#include "RODCharacter.h"

// Sets default values
AFinalBoss::AFinalBoss()
{
	
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	PawnSensingComp = CreateDefaultSubobject<UPawnSensingComponent>(TEXT("PawnSensingComp"));
	//Set the peripheral vision angle to 90 degrees
	PawnSensingComp->SetPeripheralVisionAngle(30.f);
	OnActorHit.AddDynamic(this, &AFinalBoss::OnHit);
	
	
}

AFinalBoss::~AFinalBoss()
{
	if (ManagerPtr.IsValid())
	{
		ManagerPtr.Get()->EnemyKilled();
	}
}

// Called when the game starts or when spawned
void AFinalBoss::BeginPlay()
{
	Super::BeginPlay();

	World = GetWorld();

	if (PawnSensingComp)
	{
		PawnSensingComp->OnSeePawn.AddDynamic(this, &AFinalBoss::OnSeePlayer);
	}

	for (TActorIterator<ARODCharacter>ActorItr(GetWorld()); ActorItr; ++ActorItr)
	{
		if (FString(TEXT("RODCharacter_C_0")).Equals(ActorItr->GetName()))
		{
			//finding pawn
			PlayerPawn = *ActorItr;
		}
	}
	
}

void AFinalBoss::OnSeePlayer(APawn * Pawn)
{
	ABossAIController* AIController = Cast<ABossAIController>(GetController());
	//Set the seen target on the blackboard
	if (AIController)
	{

		GLog->Log("Oh hello there");
		AIController->SetSeenTarget(Pawn);

	}

}


void AFinalBoss::ShotTimerExpired() {
	bCanFire = true;
}



void AFinalBoss::UpdateLife(float Damage)
{
	Health -= Damage;

	if (Health <= 0) {

		Destroy();

	}

}

// Called every frame
void AFinalBoss::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void AFinalBoss::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AFinalBoss::AddManager(UGameManager * Manager)
{
	if (!ManagerPtr.IsValid())
	{
		ManagerPtr = Manager;
	}
}

void AFinalBoss::OnHit(AActor * SelfActor, AActor * OtherActor, FVector NormalImpulse, const FHitResult & Hit)
{

	ABossAIController* AIController = Cast<ABossAIController>(GetController());
	//Set the seen target on the blackboard
	if (AIController)
	{

		ARODCharacter* RODCharacter = Cast<ARODCharacter>(OtherActor);

		if (RODCharacter != NULL && RODCharacter->IsInMeleeAttack())
		{
			UpdateLife(RODCharacter->GetMeleeDamage());
			GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, FString::Printf(TEXT("Enemigo golpeado! %f"), Health));

			return;
		}

		if (OtherActor->IsA(ABullet::StaticClass()))
		{
			ABullet* Bullet = Cast<ABullet>(OtherActor);

			UpdateLife(Bullet->GetDamage());
			//ManagerPtr.Get()->IncrementShotsOnTarget();
			Bullet->Destroy();
		}

	}

}

void AFinalBoss::Shoot()
{
	if (bCanFire) {
		bCanFire = false;
		FVector EnemyLocation = GetActorLocation();
		FVector PlayerLocation = PlayerPawn->GetActorLocation();
		FVector DirectionVector = FVector(PlayerLocation.X - EnemyLocation.X, PlayerLocation.Y - EnemyLocation.Y, .0f).GetSafeNormal();
		FRotator Rotation = DirectionVector.Rotation();
		EnemyLocation = EnemyLocation + (DirectionVector * 100);
		World->SpawnActor<ABullet>(EnemyLocation, Rotation);
		//UGameplayStatics::PlaySoundAtLocation(this, FireSound, GetActorLocation());

		World->GetTimerManager().SetTimer(TimerHandle_ShotTimerExpired, this, &AFinalBoss::ShotTimerExpired, 0.4f);
	}
}


void AFinalBoss::MoveToPlayer() {
	//float Distance = DistanceToPlayer();
	//if (Distance > 500.0f) {
	FVector ActualLocation = GetActorLocation();
	FVector DirectionVector = PlayerPawn->GetActorLocation() - ActualLocation;

	FVector Movement = (DirectionVector.GetSafeNormal()*(DeltaSeconds*MoveSpeed));
	const FRotator NewRotation(0, 0, 0);
	FHitResult Hit(1.f);
	RootComponent->MoveComponent(Movement, NewRotation, true);

	if (Hit.IsValidBlockingHit())
	{
		const FVector Normal2D = Hit.Normal.GetSafeNormal2D();
		const FVector Deflection = FVector::VectorPlaneProject(Movement, Normal2D) * (1.f - Hit.Time);
		RootComponent->MoveComponent(Deflection, NewRotation, true);
	}
	//}
}
float AFinalBoss::DistanceToPlayer()
{
	FVector PlayerPoint = PlayerPawn->GetActorLocation();
	FVector EnemyPoint = GetActorLocation();
	float x, y, z;
	x = PlayerPoint.X - EnemyPoint.X;
	x = x * x;
	y = PlayerPoint.Y - EnemyPoint.Y;
	y = y * y;
	z = PlayerPoint.Z - EnemyPoint.Z;
	z = z * z;

	return FMath::Sqrt(x + y + z);
}
