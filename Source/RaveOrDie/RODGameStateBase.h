// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "RODGameStateBase.generated.h"

class UGameManager;

UCLASS()
class RAVEORDIE_API ARODGameStateBase : public AGameStateBase
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable, Category = "Manager")
	UGameManager* GetGameManager();

private:
	TWeakObjectPtr<UGameManager> GameManager;
	
	
};
