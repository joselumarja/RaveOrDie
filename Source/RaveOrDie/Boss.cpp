// Fill out your copyright notice in the Description page of Project Settings.

#include "Boss.h"
#include "MyAIController.h"
#include "Engine.h"
#include "BehaviorTree/BehaviorTree.h"
#include "Perception/PawnSensingComponent.h"
#include "GameManager.h"
#include "VeryBigBullet.h"
#include "RODCharacter.h"

ABoss::ABoss() :Super() {
	PrimaryActorTick.bCanEverTick = true;
	Health = 300.0f;
}


void ABoss::BeginPlay()
{
	Super::BeginPlay();

	if (PawnSensingComp)
	{
		PawnSensingComp->OnSeePawn.AddDynamic(this, &AEnemigo::OnSeePlayer);
	}

}


void ABoss::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ABoss::Shoot() 
{
	
		FVector EnemyLocation = GetActorLocation();
		EnemyLocation.Z += 30;
		FVector PlayerLocation = PlayerPawn->GetActorLocation();
		FVector DirectionVector = FVector(PlayerLocation.X - EnemyLocation.X, PlayerLocation.Y - EnemyLocation.Y, .0f).GetSafeNormal();

		FRotator Rotation = DirectionVector.Rotation();
		EnemyLocation = EnemyLocation + (DirectionVector * 100);
		GetWorld()->SpawnActor<AVeryBigBullet>(EnemyLocation, Rotation);

}
