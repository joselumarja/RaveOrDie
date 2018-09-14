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

	void EnemyKilled();

	static TWeakObjectPtr<UGameManager> GetManager();

	void InitializeGameManager();

	FORCEINLINE void IncrementShots() { Shots++; }

	FORCEINLINE void IncrementShotsOnTarget() { ShotsOnTarget++; }

	TSubclassOf<class AMeleeEnemigo> MyMeleeBlueprint;

	TSubclassOf<class ARangedEnemigo> MyRangedBlueprint;

	TSubclassOf<class ABoss> MyBossBlueprint;

private:

	UGameManager();

	static TWeakObjectPtr<UGameManager> Manager;

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
