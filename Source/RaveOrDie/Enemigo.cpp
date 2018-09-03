// Fill out your copyright notice in the Description page of Project Settings.

#include "Enemigo.h"
#include "MyAIController.h"
#include "Engine.h"
#include "BehaviorTree/BehaviorTree.h"
#include "Perception/PawnSensingComponent.h"
#include "GameManager.h"
#include "Bullet.h"
#include "RODCharacter.h"


// Sets default values
AEnemigo::AEnemigo()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	PawnSensingComp = CreateDefaultSubobject<UPawnSensingComponent>(TEXT("PawnSensingComp"));
	//Set the peripheral vision angle to 90 degrees
	PawnSensingComp->SetPeripheralVisionAngle(30.f);
	OnActorHit.AddDynamic(this, &AEnemigo::OnHit);

	World = GetWorld();
}

AEnemigo::~AEnemigo()
{
	if (ManagerPtr.IsValid())
	{
		ManagerPtr.Get()->EnemyKilled();
	}
}

// Called when the game starts or when spawned
void AEnemigo::BeginPlay()
{
	Super::BeginPlay();
	if (PawnSensingComp)
	{
		PawnSensingComp->OnSeePawn.AddDynamic(this, &AEnemigo::OnSeePlayer);
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

// Called every frame
void AEnemigo::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AEnemigo::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}


void AEnemigo::OnSeePlayer(APawn* Pawn)
{
	AMyAIController* AIController = Cast<AMyAIController>(GetController());
	//Set the seen target on the blackboard
	if (AIController)
	{
		GLog->Log("Oh hello there");
		AIController->SetSeenTarget(Pawn);
	}
}

void AEnemigo::OnHit(AActor* SelfActor, AActor* OtherActor, FVector NormalImpulse, const FHitResult& Hit)
{
	//GetMesh()->PlayAnimation(HitAnim, false);
	AMyAIController* AIController = Cast<AMyAIController>(GetController());
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
			ManagerPtr.Get()->IncrementShotsOnTarget();
			Bullet->Destroy();
		}

	}
}

void AEnemigo::UpdateLife(float Damage) {
	Health -= Damage;

	if (Health <= 0) {

		Destroy();

	}
}

void AEnemigo::AddManager(UGameManager* Manager)
{

	if (!ManagerPtr.IsValid())
	{
		ManagerPtr = Manager;
	}
}

void AEnemigo::ShotTimerExpired(){
	bCanFire = true;
}

void AEnemigo::Shoot(){

	/*FVector PlayerPoint = PlayerPawn->GetActorLocation();
	FVector EnemyPoint = GetActorLocation();
	float x, y, z;
	x = PlayerPoint.X - EnemyPoint.X;
	x = x * x;
	y = PlayerPoint.Y - EnemyPoint.Y;
	y = y * y;
	z = PlayerPoint.Z - EnemyPoint.Z;
	z = z * z;

	return FMath::Sqrt(x + y + z);

	*/
	if (bCanFire){
		bCanFire = false;
		FVector EnemyLocation = GetActorLocation();
		FVector PlayerLocation = PlayerPawn->GetActorLocation();
		FVector DirectionVector = FVector(PlayerLocation.X - EnemyLocation.X, PlayerLocation.Y - EnemyLocation.Y, .0f).GetSafeNormal();
		FRotator Rotation = DirectionVector.Rotation();
		EnemyLocation = EnemyLocation + (DirectionVector * 100);
		World->SpawnActor<ABullet>(EnemyLocation, Rotation);
		//UGameplayStatics::PlaySoundAtLocation(this, FireSound, GetActorLocation());

		World->GetTimerManager().SetTimer(TimerHandle_ShotTimerExpired, this, &AEnemigo::ShotTimerExpired, 0.4f);

	}
}