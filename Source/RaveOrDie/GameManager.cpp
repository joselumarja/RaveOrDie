// Fill out your copyright notice in the Description page of Project Settings.

#include "GameManager.h"
#include "Enemigo.h"
#include "RangedEnemigo.h"
#include "Boss.h"
#include "MeleeEnemigo.h"
#include "Runtime/Core/Public/Containers/Array.h"
#include "Engine.h"

UGameManager::UGameManager() 
{
	/*
	static ConstructorHelpers::FObjectFinder<UBlueprint> ItemBlueprint(TEXT("Game/AI/Enemigo/BP_MeleeEnemigo.BP_MeleeEnemigo"));
	if (ItemBlueprint.Object) {
		MyMeleeBlueprint = (UClass*)ItemBlueprint.Object->GeneratedClass;
	}

	static ConstructorHelpers::FObjectFinder<UBlueprint> RangedItemBlueprint(TEXT("Game/AI/Enemigo/BP_RangedEnemigo.BP_RangedEnemigo"));
	if (RangedItemBlueprint.Object) {
		MyRangedBlueprint = (UClass*)RangedItemBlueprint.Object->GeneratedClass;
	}


	static ConstructorHelpers::FObjectFinder<UBlueprint> BossItemBlueprint(TEXT("Game/AI/FinaBoss/BP_Boss.BP_Boss"));
	if (BossItemBlueprint.Object) {
		MyBossBlueprint = (UClass*)BossItemBlueprint.Object->GeneratedClass;
	}
	*/
}

void UGameManager::EnemyKilled()
{
	EnemiesKilled++;
}

void UGameManager::ResetStatistics()
{

}

void UGameManager::GameOver()
{

}



