// Fill out your copyright notice in the Description page of Project Settings.

#include "RangedEnemigo.h"
#include "MyAIController.h"
#include "Engine.h"
#include "BehaviorTree/BehaviorTree.h"
#include "Perception/PawnSensingComponent.h"
#include "GameManager.h"
#include "EnemyLightBullet.h"
#include "RODCharacter.h"

ARangedEnemigo::ARangedEnemigo() :Super() {

	auto AnimAsset = ConstructorHelpers::FObjectFinder<UAnimSequence>(TEXT("AnimSequence'/Game/AI/ZombieGirl/Animations/Dying.Dying'"));
	if (AnimAsset.Succeeded())
	{
		DeadAnimation = AnimAsset.Object;
	}
}


void ARangedEnemigo::BeginPlay()
{
	Super::BeginPlay();

	if (PawnSensingComp)
	{
		PawnSensingComp->OnSeePawn.AddDynamic(this, &AEnemigo::OnSeePlayer);
	}

}


void ARangedEnemigo::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ARangedEnemigo::Shoot() 
{

	FVector EnemyLocation = GetActorLocation();
	FVector PlayerLocation = PlayerPawn->GetActorLocation();
	FVector DirectionVector = FVector(PlayerLocation.X - EnemyLocation.X, PlayerLocation.Y - EnemyLocation.Y, .0f).GetSafeNormal();
	FRotator Rotation = DirectionVector.Rotation();
	EnemyLocation = EnemyLocation + (DirectionVector * 100);
	GetWorld()->SpawnActor<AEnemyLightBullet>(EnemyLocation, Rotation);

}
