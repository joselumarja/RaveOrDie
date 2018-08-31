// Fill out your copyright notice in the Description page of Project Settings.

#include "HUDManager.h"
#include "UObject/ConstructorHelpers.h"
#include "Blueprint/UserWidget.h"
#include "TextWidgetTypes.h"
#include "Runtime/UMG/Public/Components/Image.h"
#include "Runtime/UMG/Public/Components/ProgressBar.h"
#include "Runtime/UMG/Public/Components/TextBlock.h"



#define LOCTEXT_NAMESPACE "HUD Manager"

// Sets default values
AHUDManager::AHUDManager()
{
	auto FHUDWidget = ConstructorHelpers::FClassFinder<UUserWidget>(TEXT("'/Game/Blueprints/HUD'"));

	if (FHUDWidget.Succeeded())
	{
		HUDWidget = FHUDWidget.Class;
	}

	auto FKnife = ConstructorHelpers::FObjectFinder<UTexture2D>(TEXT("'/Game/Blueprints/Knife.Knife'"));

	if (FKnife.Succeeded())
	{
		Knife = FKnife.Object;
	}

	auto FGun = ConstructorHelpers::FObjectFinder<UTexture2D>(TEXT("'/Game/Blueprints/Gun.Gun'"));

	if (FGun.Succeeded())
	{
		Gun = FGun.Object;
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

void AHUDManager::TurnToMelee()
{
	pWeapon->SetBrushFromTexture(Knife,false);
}

void AHUDManager::TurnToGun()
{
	pWeapon->SetBrushFromTexture(Gun,false);
}

void AHUDManager::StartBossFight(const float & MAXLIFE, const float & LIFE, const FString & Name)
{
	pBossLife->SetPercent(LIFE / MAXLIFE);
	pBoss->SetText(FText::Format(LOCTEXT("BossName", "{0}"), FText::FromString(Name)));
	pBossLife->SetVisibility(ESlateVisibility::Visible);
	pBoss->SetVisibility(ESlateVisibility::Visible);
}

void AHUDManager::FinishBossFight()
{
	pBoss->SetVisibility(ESlateVisibility::Hidden);
	pBossLife->SetVisibility(ESlateVisibility::Hidden);
}

void AHUDManager::UpdateLife(const float & MAXLIFE, const float & LIFE)
{
	pLife->SetPercent(LIFE/MAXLIFE);
}

void AHUDManager::UpdateAmo(const uint32 & Amo)
{
	pAmo->SetText(FText::Format(LOCTEXT("AMO", "{0}"), FText::AsNumber(Amo)));
}

void AHUDManager::UpdateTime(const uint8 & Hours, const uint8 & Minutes, const uint8 & Seconds)
{
	pTime->SetText(FText::Format(LOCTEXT("Time", "{0}:{1}:{2}"), FText::AsNumber(Hours), FText::AsNumber(Minutes), FText::AsNumber(Seconds)));
}


#undef LOCTEXT_NAMESPACE