// Fill out your copyright notice in the Description page of Project Settings.

#include "RangedEnemigo.h"
#include "MyAIController.h"
#include "Engine.h"
#include "BehaviorTree/BehaviorTree.h"
#include "Perception/PawnSensingComponent.h"
#include "GameManager.h"
#include "Bullet.h"
#include "RODCharacter.h"

ARangedEnemigo::ARangedEnemigo() :Super() {
	PrimaryActorTick.bCanEverTick = true;
	/*PawnSensingComp = CreateDefaultSubobject<UPawnSensingComponent>(TEXT("PawnSensingComp"));
	//Set the peripheral vision angle to 90 degrees
	PawnSensingComp->SetPeripheralVisionAngle(30.f);*/
	OnActorHit.AddDynamic(this, &AEnemigo::OnHit);
}


void ARangedEnemigo::BeginPlay()
{
	Super::BeginPlay();
	World = GetWorld();

	if (PawnSensingComp)
	{
		PawnSensingComp->OnSeePawn.AddDynamic(this, &AEnemigo::OnSeePlayer);
	}

}


void ARangedEnemigo::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ARangedEnemigo::Shoot() {
	if (bCanFire) {
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
