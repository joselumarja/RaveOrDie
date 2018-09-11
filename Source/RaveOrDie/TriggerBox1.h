// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/TriggerBox.h"
#include "TriggerBox1.generated.h"

class ASongManager;

/**
 * 
 */
UCLASS()
class RAVEORDIE_API ATriggerBox1 : public ATriggerBox
{
	GENERATED_BODY()
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	ASongManager* SongManagerPtr;

public:

	ATriggerBox1();

	UFUNCTION()
		void OnOverlapBegin(AActor* OverlappedActor, AActor* OtherActor);

	UFUNCTION()
		void OnOverlapEnd(AActor* OverlappedActor, AActor* OtherActor);
	
	TSubclassOf<class AEnemigo> MyItemBlueprint;

	TSubclassOf<class AEnemigo> MyRangedBlueprint;

	TSubclassOf<class AFinalBoss> MyBossBlueprint;
};
