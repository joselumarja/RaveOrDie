// Fill out your copyright notice in the Description page of Project Settings.

#include "SongManager.h"
#include "Engine.h"
#include "Runtime/Core/Public/Containers/Array.h"

// Sets default values
ASongManager::ASongManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ASongManager::BeginPlay()
{
	Super::BeginPlay();
	World = GetWorld();
}

// Called every frame
void ASongManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}




/*TArray<FString> ASongManager::GetAllSongs() {
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
}*/