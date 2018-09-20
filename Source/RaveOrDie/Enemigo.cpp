// Fill out your copyright notice in the Description page of Project Settings.

#include "Enemigo.h"
#include "MyAIController.h"
#include "Engine.h"
#include "BehaviorTree/BehaviorTree.h"
#include "Perception/PawnSensingComponent.h"
#include "GameManager.h"
#include "Bullet.h"
#include "RODCharacter.h"
#include "Subject.h"
#include "RODGameStateBase.h"
#include "Evento.h"


// Sets default values
AEnemigo::AEnemigo()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	PawnSensingComp = CreateDefaultSubobject<UPawnSensingComponent>(TEXT("PawnSensingComp"));
	//Set the peripheral vision angle to 90 degrees
	PawnSensingComp->SetPeripheralVisionAngle(90.f);
	Health = 100.0f;

}

// Called when the game starts or when spawned
void AEnemigo::BeginPlay()
{
	Super::BeginPlay();
	World = GetWorld();

	EnemySubject = NewObject<USubject>();
	EnemySubject->AddObserver(Cast<ARODGameStateBase>(UGameplayStatics::GetGameState(GetWorld()))->GetGameManager());
	PlayerPawn = Cast<ARODCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(),0));

}

// Called every frame
void AEnemigo::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	DeltaSeconds = DeltaTime;
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
			EnemySubject->Notify(this, EEvent::EVENT_SHOT_ON_TARGET);
			Bullet->Destroy();
		}

	}
}

void AEnemigo::UpdateLife(float Damage) {
	Health -= Damage;

	if (Health <= 0) {

		EnemySubject->Notify(this, EEvent::EVENT_KILL);
		Destroy();

	}
}

void AEnemigo::ShotTimerExpired(){
	bCanFire = true;
}


void AEnemigo::MoveToPlayer() {
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
float AEnemigo::DistanceToPlayer()
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
