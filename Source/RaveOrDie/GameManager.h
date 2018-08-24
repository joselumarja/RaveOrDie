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

	static UGameManager* GetManager();

private:

	UGameManager();

	static UGameManager* Manager;

	uint32 EnemiesKilled;
	
	void InitializeGameManager();

	bool bIsGameSesionInProgress;

	void ResetStatistics();

	void GameOver();

	uint32 Score;

	uint32 Kills;

	uint32 Shots;

	float Accuracy;
	
};
