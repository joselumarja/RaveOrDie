// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Observer.h"
#include "GameManager.generated.h"

class UUserWidget;
class UTextBlock;

UENUM()
enum class EEnemigo : uint8
{
	MELEE,
	RANGED,
	BOSS
};

class AEnemigo;

UCLASS()
class RAVEORDIE_API UGameManager : public UObject, public IObserver
{
	GENERATED_BODY()
	
public:

	UGameManager();

	void SetWorld(UWorld *World);

	void OnNotify(UObject* Entity, EEvent Event) override;

	TSubclassOf<class AMeleeEnemigo> MyMeleeBlueprint;

	TSubclassOf<class ARangedEnemigo> MyRangedBlueprint;

	TSubclassOf<class ABoss> MyBossBlueprint;

	void InitializeEnemies();

	void SpawnEnemies(int32 Enemies, FVector Position, FRotator EnemiesRotation);

private:

	TSubclassOf<UUserWidget> FinishWidget;

	TWeakObjectPtr<UUserWidget> pFinishWidget;

	TWeakObjectPtr<UTextBlock> pWinText;

	TWeakObjectPtr<UTextBlock> pFailText;

	void InitializeFinishWidget();

	void ObjectiveAccomplished();

	void IncreaseEventCounter(EEvent Event);

	TMap<EEvent, uint32> EventsCounter;

	uint32 EnemiesKilled;

	bool bIsGameSesionInProgress;

	void GameOver();

	uint32 Score;

	uint32 Kills;

	uint32 Shots;

	uint32 ShotsOnTarget;

	float Accuracy;
	
	uint8 EnemiesAlived;

	uint8 EnemiesKilledPerRound;

	TArray<TSubclassOf<AEnemigo>> EnemyClasses;

	FVector GetRandomLocation(FVector &Location, float &SafeRange) const;

	void SpawnEnemy(FVector &Location, FRotator Rotation);

	EEnemigo GetRandomEnemyClass() const;

	float SafeSpawnRange;

	float DistanceBetweenAreas;

	UWorld *World;
};


