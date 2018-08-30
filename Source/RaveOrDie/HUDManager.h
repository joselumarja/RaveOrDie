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

	void TurnToMelee();

	void TurnToGun();

	void StartBossFight(const float &MAXLIFE,const float &LIFE,const FString &Name);

	void FinishBossFight();

	void UpdateLife(const float &MAXLIFE,const float &LIFE);

	void UpdateAmo(const uint32 &Amo);

	void UpdateTime(const uint8 &Hours,const uint8 &Minutes,const uint8 &Seconds);

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
