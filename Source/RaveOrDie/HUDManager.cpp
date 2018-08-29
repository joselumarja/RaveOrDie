// Fill out your copyright notice in the Description page of Project Settings.

#include "HUDManager.h"
#include "UObject/ConstructorHelpers.h"
#include "Blueprint/UserWidget.h"
#include "Runtime/UMG/Public/Components/Image.h"
#include "Runtime/UMG/Public/Components/ProgressBar.h"
#include "Runtime/UMG/Public/Components/TextBlock.h"

#define LOCKTEXT_NAMESPACE "HUD Manager"

// Sets default values
AHUDManager::AHUDManager()
{
	auto FHUDWidget = ConstructorHelpers::FClassFinder<UUserWidget>(TEXT("'/Game/Blueprints/HUD'"));

	if (FHUDWidget.Succeeded())
	{
		HUDWidget = FHUDWidget.Class;
	}
}

// Called when the game starts or when spawned
void AHUDManager::BeginPlay()
{
	Super::BeginPlay();
	
	if (HUDWidget) // Check if the Asset is assigned in the blueprint.
	{
		// Create the widget and store it.
		pHUDWidget = CreateWidget<UUserWidget>(GetGameInstance(), HUDWidget);

		// now you can use the widget directly since you have a reference for it.
		// Extra check to  make sure the pointer holds the widget.
		if (pHUDWidget.IsValid())
		{
			// let add it to the view port
			pHUDWidget->AddToViewport();

			pAmo = (UTextBlock*)pHUDWidget->GetWidgetFromName("Amo");

			pBoss = (UTextBlock*)pHUDWidget->GetWidgetFromName("BossEnemy");

			pTime = (UTextBlock*)pHUDWidget->GetWidgetFromName("RunTime");

			pBossLife = (UProgressBar*)pHUDWidget->GetWidgetFromName("BossFightLife");

			pLife = (UProgressBar*)pHUDWidget->GetWidgetFromName("Life");

			pWeapon = (UImage*)pHUDWidget->GetWidgetFromName("Weapon");

		}
	}
}


#undef LOCKTEXT_NAMESPACE

