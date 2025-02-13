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
	auto FHUDWidget = ConstructorHelpers::FClassFinder<UUserWidget>(TEXT("'/Game/Blueprints/Menus/HUD'"));

	if (FHUDWidget.Succeeded())
	{
		HUDWidget = FHUDWidget.Class;
	}

	auto FKnife = ConstructorHelpers::FObjectFinder<UTexture2D>(TEXT("'/Game/Blueprints/Menus/Knife.Knife'"));

	if (FKnife.Succeeded())
	{
		Knife = FKnife.Object;
	}

	auto FGun = ConstructorHelpers::FObjectFinder<UTexture2D>(TEXT("'/Game/Blueprints/Menus/Gun.Gun'"));

	if (FGun.Succeeded())
	{
		Gun = FGun.Object;
	}
}

AHUDManager::~AHUDManager()
{
	if (pHUDWidget.IsValid())
	{
		pHUDWidget->RemoveFromViewport();
	}
}

void AHUDManager::BeginPlay()
{
	Super::BeginPlay();
	
	if (HUDWidget) 
	{

		pHUDWidget = CreateWidget<UUserWidget>(GetGameInstance(), HUDWidget);

		if (pHUDWidget.IsValid())
		{

			pHUDWidget->AddToViewport();

			pAmo = (UTextBlock*)pHUDWidget->GetWidgetFromName("Amo");

			pTime = (UTextBlock*)pHUDWidget->GetWidgetFromName("RunTime");

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



void AHUDManager::UpdateLife(const float & MAXLIFE, const float & LIFE)
{
	pLife->SetPercent(LIFE/MAXLIFE);
}

void AHUDManager::UpdateAmo(const uint32 &Amo)
{
	if (Amo > 0)
	{
		pAmo->SetText(FText::Format(LOCTEXT("AMO", "{0}"), FText::AsNumber(Amo)));
	}
	else
	{
		pAmo->SetText(FText::Format(LOCTEXT("AMO", "{0}"), FText::FromString("RECARGA!!")));
	}
}

void AHUDManager::UpdateTime(const FTimeStruct &Time)
{
	pTime->SetText(FText::Format(LOCTEXT("Time", "{0}:{1}:{2}"), FText::AsNumber(Time.Minutes), FText::AsNumber(Time.Seconds), FText::AsNumber(Time.Tenths)));
}


#undef LOCTEXT_NAMESPACE