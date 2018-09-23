// Fill out your copyright notice in the Description page of Project Settings.

#include "MeleeEnemigo.h"
#include "MyAIController.h"
#include "Engine.h"
#include "BehaviorTree/BehaviorTree.h"
#include "Perception/PawnSensingComponent.h"
#include "GameManager.h"
#include "Bullet.h"
#include "RODCharacter.h"
#include "Runtime/Engine/Classes/Components/SphereComponent.h"

AMeleeEnemigo::AMeleeEnemigo() :Super() {

	auto AnimAsset = ConstructorHelpers::FObjectFinder<UAnimSequence>(TEXT("AnimSequence'/Game/AI/ZombieBoy/Animations/Dying.Dying'"));
	if (AnimAsset.Succeeded())
	{
		DeadAnimation = AnimAsset.Object;
	}

	MeleeDamage = 25.0f;
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
