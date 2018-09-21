// Fill out your copyright notice in the Description page of Project Settings.

#include "GameManager.h"
#include "Enemigo.h"
#include "RangedEnemigo.h"
#include "RODCharacter.h"
#include "Boss.h"
#include "MeleeEnemigo.h"
#include "Runtime/Core/Public/Containers/Array.h"
#include "Engine.h"
#include "TimeStruct.h"
#include "MySaveGame.h"

UGameManager::UGameManager() 
{
	EventsCounter.Add(EEvent::EVENT_SHOT, 0);
	EventsCounter.Add(EEvent::EVENT_SHOT_ON_TARGET, 0);
	EventsCounter.Add(EEvent::EVENT_KILL, 0);

	InitializeEnemies();
	
}

void UGameManager::ResetStatistics()
{

}

void UGameManager::GameOver()
{
	UGameplayStatics::OpenLevel(GetWorld(), TEXT("/Game/Maps/MainMenu.MainMenu"), TRAVEL_Absolute);
	
}

void UGameManager::ObjectiveAccomplished()
{
	FTimeStruct PlayTime = Cast<ARODCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0))->GetPlayTime();

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
	GameOver();
}



void UGameManager::SpawnEnemies(int Enemies, FVector Position) {
	int32 aux;
	for (int i = 0; i < Enemies; i++) {
		FVector EnemySpawnLocation = GetRandomLocation();
		FRotator Rotation(0.0f, 180.0f, 0.0f);
		aux = GetRandomEnemyClass();
		if (aux == 0){
			AMeleeEnemigo* DroppedItem = GetWorld()->SpawnActor<AMeleeEnemigo>(MyMeleeBlueprint, EnemySpawnLocation, Rotation);
			
		}
		else if (aux == 1) {
			ARangedEnemigo* DroppedItem2 = GetWorld()->SpawnActor<ARangedEnemigo>(MyRangedBlueprint, EnemySpawnLocation, Rotation);
		}
		else if (aux == 3) {
			ABoss* DroppedItem3 = GetWorld()->SpawnActor<ABoss>(MyBossBlueprint, EnemySpawnLocation, Rotation);

		}
		EnemiesAlived++;
	}
	
}

void UGameManager::OnNotify(UObject* Entity, EEvent Event)
{
	switch (Event)
	{
		case EEvent::EVENT_DEAD:
			GameOver();
			break;

		case EEvent::EVENT_FINISH:
			ObjectiveAccomplished();
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

int32 UGameManager::GetRandomEnemyClass() const
{
	return FMath::RandRange(1, 3);
}

// Gets a random place to spawn an enemy
FVector UGameManager::GetRandomLocation() const
{
	float x;
	float y;
	float z = PlayerPawn->GetActorLocation().Z;

	y = FMath::RandRange(-1950, 1950);
	x = FMath::RandRange(2900, 3000);
	FVector RandomLocation(x, y, z);
	return RandomLocation;
}


void UGameManager::InitializeEnemies() {
	static ConstructorHelpers::FObjectFinder<UBlueprint> ItemBlueprint(TEXT("Blueprint'/Game/AI/ZombieBoy/BP_MeleeEnemigo.BP_MeleeEnemigo'"));
	if (ItemBlueprint.Object) {
		MyMeleeBlueprint = (UClass*)ItemBlueprint.Object->GeneratedClass;
	}

	static ConstructorHelpers::FObjectFinder<UBlueprint> RangedItemBlueprint(TEXT("Blueprint'/Game/AI/ZombieGirl/BP_RangedEnemigo.BP_RangedEnemigo'"));
	if (RangedItemBlueprint.Object) {
		MyRangedBlueprint = (UClass*)RangedItemBlueprint.Object->GeneratedClass;
	}


	static ConstructorHelpers::FObjectFinder<UBlueprint> BossItemBlueprint(TEXT("Blueprint'/Game/AI/FinaBoss/BP_Boss.BP_Boss'"));
	if (BossItemBlueprint.Object) {
		MyBossBlueprint = (UClass*)BossItemBlueprint.Object->GeneratedClass;
	}

}