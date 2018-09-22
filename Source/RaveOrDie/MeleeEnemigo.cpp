// Fill out your copyright notice in the Description page of Project Settings.

#include "MeleeEnemigo.h"
#include "MyAIController.h"
#include "Engine.h"
#include "BehaviorTree/BehaviorTree.h"
#include "Perception/PawnSensingComponent.h"
#include "GameManager.h"
#include "Bullet.h"
#include "RODCharacter.h"

AMeleeEnemigo::AMeleeEnemigo() :Super() {
	PrimaryActorTick.bCanEverTick = true;
	MeleeDamage = 25.0f;
	OnActorHit.AddDynamic(this, &AEnemigo::OnHit);
}


void AMeleeEnemigo::BeginPlay()
{
	Super::BeginPlay();

	if (PawnSensingComp)
	{
		PawnSensingComp->OnSeePawn.AddDynamic(this, &AEnemigo::OnSeePlayer);
	}


}


void AMeleeEnemigo::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
