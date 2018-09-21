// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/TriggerBox.h"
#include "TriggerBoxMeta.generated.h"

class USubject;

UCLASS()
class RAVEORDIE_API ATriggerBoxMeta : public ATriggerBox
{
	GENERATED_BODY()
	
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:

	ATriggerBoxMeta();

	UFUNCTION()
		void OnOverlapBegin(AActor* OverlappedActor, AActor* OtherActor);

	UFUNCTION()
		void OnOverlapEnd(AActor* OverlappedActor, AActor* OtherActor);
private:

	TWeakObjectPtr<USubject> MetaTriggerBoxSubject;
	
};
