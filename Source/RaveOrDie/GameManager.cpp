// Fill out your copyright notice in the Description page of Project Settings.

#include "GameManager.h"
#include "Enemigo.h"
#include "RangedEnemigo.h"
#include "RODCharacter.h"
#include "Boss.h"
#include "MeleeEnemigo.h"
#include "Runtime/Core/Public/Containers/Array.h"
#include "Engine.h"

UGameManager::UGameManager() 
{
	
	static ConstructorHelpers::FObjectFinder<UBlueprint> ItemBlueprint(TEXT("Blueprint'/Game/AI/Enemigo/BP_MeleeEnemigo.BP_MeleeEnemigo'"));
	if (ItemBlueprint.Object) {
		MyMeleeBlueprint = (UClass*)ItemBlueprint.Object->GeneratedClass;
	}

	static ConstructorHelpers::FObjectFinder<UBlueprint> RangedItemBlueprint(TEXT("Blueprint'/Game/AI/Enemigo/BP_RangedEnemigo.BP_RangedEnemigo'"));
	if (RangedItemBlueprint.Object) {
		MyRangedBlueprint = (UClass*)RangedItemBlueprint.Object->GeneratedClass;
	}


	static ConstructorHelpers::FObjectFinder<UBlueprint> BossItemBlueprint(TEXT("Blueprint'/Game/AI/FinaBoss/BP_Boss.BP_Boss'"));
	if (BossItemBlueprint.Object) {
		MyBossBlueprint = (UClass*)BossItemBlueprint.Object->GeneratedClass;
	}
	
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



void UGameManager::SpawnEnemies(int Enemies) {
	int32 aux;
	for (int i = 0; i < Enemies; i++) {
		FVector EnemySpawnLocation = GetRandomLocation();
		FRotator Rotation(0.0f, 180.0f, 0.0f);
		aux = GetRandomEnemyClass();
		if (aux == 0){
			AMeleeEnemigo* DroppedItem = GetWorld()->SpawnActor<AMeleeEnemigo>(MyMeleeBlueprint, EnemySpawnLocation, Rotation);
			
		}
		else if (aux == 1) {
			ARangedEnemigo* DroppedItem2 = GetWorld()->SpawnActor<ARangedEnemigo>(MyRangedBlueprint, EnemySpawnLocation, Rotation);
		}

		EnemiesAlived++;
	}
	
}



int32 UGameManager::GetRandomEnemyClass() const
{
	return FMath::RandRange(0, 2);
}

// Gets a random place to spawn an enemy
FVector UGameManager::GetRandomLocation() const
{
	float x;
	float y;
	float z = PlayerPawn->GetActorLocation().Z;

	y = FMath::RandRange(-1950, 1950);
	x = FMath::RandRange(2900, 3000);
	FVector RandomLocation(x, y, z);
	return RandomLocation;
}