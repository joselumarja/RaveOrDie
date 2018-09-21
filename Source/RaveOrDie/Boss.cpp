// Fill out your copyright notice in the Description page of Project Settings.

#include "Boss.h"
#include "MyAIController.h"
#include "Engine.h"
#include "BehaviorTree/BehaviorTree.h"
#include "Perception/PawnSensingComponent.h"
#include "GameManager.h"
#include "EnemyBullet.h"
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

void ABoss::Shoot() {
	
		FVector EnemyLocation = GetActorLocation();
		FVector PlayerLocation = PlayerPawn->GetActorLocation();
		FVector DirectionVector = FVector(PlayerLocation.X - EnemyLocation.X, PlayerLocation.Y - EnemyLocation.Y, .0f).GetSafeNormal();

		FRotator Rotation = DirectionVector.Rotation().Add(0.0f, 15.0f, 0.0f);
		EnemyLocation = EnemyLocation + (DirectionVector * 100);
		World->SpawnActor<AEnemyBullet>(EnemyLocation, Rotation);

		Rotation = DirectionVector.Rotation();
		EnemyLocation = EnemyLocation + (DirectionVector * 100);
		World->SpawnActor<AEnemyBullet>(EnemyLocation, Rotation);

		DirectionVector = FVector(PlayerLocation.X - EnemyLocation.X, PlayerLocation.Y - EnemyLocation.Y, .0f).GetSafeNormal();
		Rotation = DirectionVector.Rotation().Add(0.0f, -15.0f, 0.0f);
		EnemyLocation = EnemyLocation + (DirectionVector * 100);
		World->SpawnActor<AEnemyBullet>(EnemyLocation, Rotation);
		//UGameplayStatics::PlaySoundAtLocation(this, FireSound, GetActorLocation());

		
}
