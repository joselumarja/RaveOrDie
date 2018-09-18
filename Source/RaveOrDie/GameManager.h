// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "GameManager.generated.h"


UCLASS()
class RAVEORDIE_API UGameManager : public UObject
{
	GENERATED_BODY()
	
public:

	UGameManager();

	void EnemyKilled();

	FORCEINLINE void IncrementShots() { Shots++; }

	FORCEINLINE void IncrementShotsOnTarget() { ShotsOnTarget++; }

	TSubclassOf<class AMeleeEnemigo> MyMeleeBlueprint;

	TSubclassOf<class ARangedEnemigo> MyRangedBlueprint;

	TSubclassOf<class ABoss> MyBossBlueprint;

private:

	uint32 EnemiesKilled;

	bool bIsGameSesionInProgress;

	void ResetStatistics();

	void GameOver();

	uint32 Score;

	uint32 Kills;

	uint32 Shots;

	uint32 ShotsOnTarget;

	float Accuracy;

	
	
};
