// Fill out your copyright notice in the Description page of Project Settings.

#include "GameManager.h"
#include "Enemigo.h"
#include "Runtime/Core/Public/Containers/Array.h"
#include "Engine.h"

TWeakObjectPtr<UGameManager> UGameManager::Manager = nullptr;

UGameManager::UGameManager() 
{

}

TWeakObjectPtr<UGameManager> UGameManager::GetManager()
{
	if (!Manager.IsValid())
	{
		Manager = NewObject<UGameManager>();
	}

	return Manager;
}

void UGameManager::InitializeGameManager()
{
	UWorld* World = GetWorld();

	if (World != NULL)
	{
		for (TActorIterator<AEnemigo>ActorItr(World); ActorItr; ++ActorItr)
		{
			ActorItr->AddManager(this);
		}
	}
}

void UGameManager::EnemyKilled()
{
	EnemiesKilled++;
}

void UGameManager::ResetStatistics()
{

}

void UGameManager::GameOver()
{

}


TArray<FString> UGameManager::GetAllSongs() {
	auto ObjectLibrary = UObjectLibrary::CreateLibrary(UObject::StaticClass(), false, true);
	ObjectLibrary->LoadAssetDataFromPath(TEXT("/Game/Songs"));
	TArray<FAssetData> AssetDatas;
	ObjectLibrary->GetAssetDataList(AssetDatas);
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, FString::Printf(TEXT("Canciones encontradas! %d"), AssetDatas.Num()));
	TArray<FString> Names = TArray<FString>();

	for (int32 i = 0; i < AssetDatas.Num(); ++i)
	{
		FAssetData& AssetData = AssetDatas[i];

		auto name = AssetData.AssetName.ToString();
		Names.Add(name);
	}
	return Names;
}
