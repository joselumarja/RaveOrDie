// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Runtime/Engine/Classes/Engine/Texture2D.h"
#include "TimeStruct.h"
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

	~AHUDManager();

	void TurnToMelee();

	void TurnToGun();

	void UpdateLife(const float &MAXLIFE,const float &LIFE);

	void UpdateAmo(const uint32 &Amo);

	void UpdateTime(const FTimeStruct &Time);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	TSubclassOf<UUserWidget> HUDWidget;

	TWeakObjectPtr<UUserWidget> pHUDWidget;
	
	TWeakObjectPtr<UTextBlock> pTime;

	TWeakObjectPtr<UTextBlock> pAmo;

	TWeakObjectPtr<UProgressBar> pLife;

	TWeakObjectPtr<UImage> pWeapon;

	UTexture2D* Knife;

	UTexture2D* Gun;
};
