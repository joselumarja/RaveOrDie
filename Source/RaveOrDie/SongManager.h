// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SongManager.generated.h"

UCLASS()
class RAVEORDIE_API ASongManager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASongManager();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UWorld* World;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;


//	UFUNCTION(BlueprintCallable, Category = "Game")
	//TArray<UObject> GetAllSongs();

};
