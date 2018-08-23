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

private:

	uint32 EnemiesKilled;
	
	void InitializeGameManager();
	
};
