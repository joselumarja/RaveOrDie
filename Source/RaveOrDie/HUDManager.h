// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "HUDManager.generated.h"

class UUserWidget;
class UTextBlock;
class UProgressBar;
class UImage;

UCLASS()
class RAVEORDIE_API AHUDManager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AHUDManager();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	TSubclassOf<UUserWidget> HUDWidget;

	TWeakObjectPtr<UUserWidget> pHUDWidget;
	
	TWeakObjectPtr<UTextBlock> pTime;

	TWeakObjectPtr<UTextBlock> pAmo;

	TWeakObjectPtr<UTextBlock> pBoss;

	TWeakObjectPtr<UProgressBar> pLife;

	TWeakObjectPtr<UProgressBar> pBossLife;

	TWeakObjectPtr<UImage> pWeapon;
};
