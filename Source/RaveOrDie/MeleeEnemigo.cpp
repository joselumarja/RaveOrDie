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
	/*PawnSensingComp = CreateDefaultSubobject<UPawnSensingComponent>(TEXT("PawnSensingComp"));
	//Set the peripheral vision angle to 90 degrees
	/*PawnSensingComp->SetPeripheralVisionAngle(30.f);
	OnActorHit.AddDynamic(this, &AMeleeEnemigo::OnHit);*/
}

AMeleeEnemigo::~AMeleeEnemigo() {
	if (ManagerPtr.IsValid())
	{
		ManagerPtr.Get()->EnemyKilled();
	}
}


void AMeleeEnemigo::BeginPlay()
{
	Super::BeginPlay();
	World = GetWorld();

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


void AMeleeEnemigo::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
