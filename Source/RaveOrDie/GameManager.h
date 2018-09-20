// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Observer.h"
#include "GameManager.generated.h"

class AEnemigo;

UCLASS()
class RAVEORDIE_API UGameManager : public UObject, public IObserver
{
	GENERATED_BODY()
	
public:

	UGameManager();

	void OnNotify(UObject* Entity, EEvent Event) override;

	TSubclassOf<class AMeleeEnemigo> MyMeleeBlueprint;

	TSubclassOf<class ARangedEnemigo> MyRangedBlueprint;

	TSubclassOf<class ABoss> MyBossBlueprint;

	void InitializeEnemies();

private:

	void IncreaseEventCounter(EEvent Event);

	TMap<EEvent, uint32> EventsCounter;

	uint32 EnemiesKilled;

	bool bIsGameSesionInProgress;

	void ResetStatistics();

	void GameOver();

	uint32 Score;

	uint32 Kills;

	uint32 Shots;

	uint32 ShotsOnTarget;

	float Accuracy;
	
	uint8 EnemiesAlived;

	uint8 EnemiesKilledPerRound;

	TArray<TSubclassOf<AEnemigo>> EnemyClasses;

	FVector GetRandomLocation() const;

	void SpawnEnemies(int Enemies, FVector Position);

	int32 GetRandomEnemyClass() const;

	TWeakObjectPtr<ACharacter> PlayerPawn;
};


