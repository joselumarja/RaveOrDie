// Fill out your copyright notice in the Description page of Project Settings.

#include "GameManager.h"
#include "RangedEnemigo.h"
#include "RODCharacter.h"
#include "Boss.h"
#include "MeleeEnemigo.h"
#include "Runtime/Core/Public/Containers/Array.h"
#include "Engine.h"
#include "TimeStruct.h"
#include "MySaveGame.h"
#include "Blueprint/UserWidget.h"
#include "TextWidgetTypes.h"
#include "Runtime/CoreUObject/Public/UObject/ConstructorHelpers.h"
#include "Runtime/UMG/Public/Components/TextBlock.h"

UGameManager::UGameManager() 
{
	EventsCounter.Add(EEvent::EVENT_SHOT, 0);
	EventsCounter.Add(EEvent::EVENT_SHOT_ON_TARGET, 0);
	EventsCounter.Add(EEvent::EVENT_KILL, 0);

	SafeSpawnRange = 130.f;
	DistanceBetweenAreas = 180.f;

	InitializeEnemies();

	SpawnedEnemies = 0;

	auto FFinishWidget = ConstructorHelpers::FClassFinder<UUserWidget>(TEXT("'/Game/Blueprints/Menus/BP_FinishScreen'"));

	if (FFinishWidget.Succeeded())
	{
		FinishWidget = FFinishWidget.Class;
	}
	
}

void UGameManager::GameOver()
{
	InitializeFinishWidget();
	pFailText->SetVisibility(ESlateVisibility::Visible);
}

void UGameManager::InitializeFinishWidget()
{
	if (FinishWidget)
	{
		pFinishWidget = CreateWidget<UUserWidget>(World->GetGameInstance(), FinishWidget);

		// now you can use the widget directly since you have a reference for it.
		// Extra check to  make sure the pointer holds the widget.
		if (pFinishWidget.IsValid())
		{

			pFinishWidget->AddToViewport();

			pWinText = (UTextBlock*)pFinishWidget->GetWidgetFromName("WinText");
			pFailText = (UTextBlock*)pFinishWidget->GetWidgetFromName("FailText");

			pWinText->SetVisibility(ESlateVisibility::Hidden);
			pFailText->SetVisibility(ESlateVisibility::Hidden);

		}
	}
}

void UGameManager::ObjectiveAccomplished()
{

	FTimeStruct PlayTime = Cast<ARODCharacter>(UGameplayStatics::GetPlayerCharacter(World, 0))->GetPlayTime();

	UMySaveGame* SaveGameInstance = Cast<UMySaveGame>(UGameplayStatics::CreateSaveGameObject(UMySaveGame::StaticClass()));
	UMySaveGame* CheckSaveGameInstance = Cast<UMySaveGame>(UGameplayStatics::LoadGameFromSlot(SaveGameInstance->SaveSlotName, SaveGameInstance->UserIndex));
	if (CheckSaveGameInstance != NULL)
	{
		SaveGameInstance = CheckSaveGameInstance;
	}
	FText Name = FText::FromString(FDateTime::Now().ToString());
	float Accuracy = ((float) EventsCounter[EEvent::EVENT_SHOT_ON_TARGET]) / ((float) EventsCounter[EEvent::EVENT_SHOT]);
	SaveGameInstance->UpdateRecords(Name, EventsCounter[EEvent::EVENT_KILL], Accuracy, PlayTime);
	UGameplayStatics::SaveGameToSlot(SaveGameInstance, SaveGameInstance->SaveSlotName, SaveGameInstance->UserIndex);

	InitializeFinishWidget();
	pWinText->SetVisibility(ESlateVisibility::Visible);
	
}



void UGameManager::SpawnEnemies(int32 Enemies, FVector Position, FRotator EnemiesRotation) {

	int NX = Enemies / 2 + Enemies % 2;
	int NY = Enemies / 2;

	SpawnedEnemies += Enemies;

	int AuxSpawnedEnemies = 0;

	FVector StartSpawnLocation = FVector(Position.X - (NX*DistanceBetweenAreas / 2), Position.Y - (NY*DistanceBetweenAreas / 2),Position.Z);

	for (int i = 0; i < NX; i++)
	{
		for (int j = 0; Enemies > AuxSpawnedEnemies && j <= NY; j++, AuxSpawnedEnemies++)
		{
			FVector NewSpawnLocation = StartSpawnLocation + (FVector(i, j, 0.f)*DistanceBetweenAreas);
			SpawnEnemy(NewSpawnLocation,EnemiesRotation);
		}
	}
	
}

void UGameManager::SpawnEnemy(FVector &Location,FRotator Rotation)
{
	EEnemigo EnemyToSpawn = GetRandomEnemyClass();
	float RandomZRotation = FMath::FRandRange(-45.f, 45.f);
	Rotation.Yaw += RandomZRotation;
	FVector EnemySpawnLocation = GetRandomLocation(Location, SafeSpawnRange);

	switch (EnemyToSpawn)
	{
	case EEnemigo::MELEE:
		World->SpawnActor<AMeleeEnemigo>(MyMeleeBlueprint, EnemySpawnLocation, Rotation);

		break;
	case EEnemigo::RANGED:
		World->SpawnActor<ARangedEnemigo>(MyRangedBlueprint, EnemySpawnLocation, Rotation);

		break;
	case EEnemigo::BOSS:
		World->SpawnActor<ABoss>(MyBossBlueprint, EnemySpawnLocation, Rotation);

		break;

	}
}

void UGameManager::SetWorld(UWorld *World)
{
	this->World = World;
}

void UGameManager::OnNotify(UObject* Entity, EEvent Event)
{
	switch (Event)
	{
		case EEvent::EVENT_DEAD:
			GameOver();
			break;

		case EEvent::EVENT_FINISH:

			if (EventsCounter[EEvent::EVENT_KILL] == SpawnedEnemies)
			{
				ObjectiveAccomplished();
			}
			break;

		default:
			IncreaseEventCounter(Event);
			break;
	}
}

void UGameManager::IncreaseEventCounter(EEvent Event)
{
	// We need to keep a counter of the number of events that have arriven,
	// in order to unlock the appropriate achievements.
	// But we do not need to increase EVERY event; just the ones related to
	// the achievements.
	EventsCounter.Add(Event, ++EventsCounter[Event]);
}

EEnemigo UGameManager::GetRandomEnemyClass()
{
	
	int32 Random = FMath::FRandRange(0,6);

	if (Random < 3)
	{
		return EEnemigo::MELEE;
	}

	if (Random < 5)
	{
		return EEnemigo::RANGED;
	}

	return EEnemigo::BOSS;

}

// Gets a random place to spawn an enemy
FVector UGameManager::GetRandomLocation(FVector &Location, float &SafeRange) const
{
	float x, y;
	float HalfSafeRange = SafeRange / 2;

	x = FMath::RandRange(Location.X-HalfSafeRange, Location.X+HalfSafeRange);
	y = FMath::RandRange(Location.Y-HalfSafeRange, Location.Y+HalfSafeRange);

	return FVector(x, y, Location.Z);

}


void UGameManager::InitializeEnemies() 
{
	
	static ConstructorHelpers::FObjectFinder<UClass> ItemBlueprint(TEXT("Blueprint '/Game/AI/ZombieBoy/BP_MeleeEnemigo.BP_MeleeEnemigo_C'"));
	if (ItemBlueprint.Object) {
		MyMeleeBlueprint = (UClass*)ItemBlueprint.Object;
	}

	static ConstructorHelpers::FObjectFinder<UClass> RangedItemBlueprint(TEXT("Blueprint'/Game/AI/ZombieGirl/BP_RangedEnemigo.BP_RangedEnemigo_C'"));
	if (RangedItemBlueprint.Object) {
		MyRangedBlueprint = (UClass*)RangedItemBlueprint.Object;
	}


	static ConstructorHelpers::FObjectFinder<UClass> BossItemBlueprint(TEXT("Blueprint '/Game/AI/FinaBoss/BP_Boss.BP_Boss_C'"));
	if (BossItemBlueprint.Object) {
		MyBossBlueprint = (UClass*)BossItemBlueprint.Object;
	}

}