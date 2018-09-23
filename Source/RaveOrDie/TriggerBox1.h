// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/TriggerBox.h"
#include "TriggerBox1.generated.h"

class UGameManager;

UCLASS()
class RAVEORDIE_API ATriggerBox1 : public ATriggerBox
{
	GENERATED_BODY()
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


public:

	ATriggerBox1();

	UFUNCTION()
		void OnOverlapBegin(AActor* OverlappedActor, AActor* OtherActor);

	UPROPERTY(Category = EnemiesSpawn, EditAnywhere, BlueprintReadWrite)
		int32 NumberOfEnemies;

	UPROPERTY(Category = EnemiesSpawn, EditAnywhere, BlueprintReadWrite)
		FVector SpawnLocation;

	UPROPERTY(Category = EnemiesSpawn, EditAnywhere, BlueprintReadWrite)
		FRotator EnemiesRotation;

private:

	UPROPERTY()
	UGameManager* GameManager;
};
