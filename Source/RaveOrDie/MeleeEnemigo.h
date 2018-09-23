// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Enemigo.h"
#include "MeleeEnemigo.generated.h"

class USphereComponent;

UCLASS()
class RAVEORDIE_API AMeleeEnemigo : public AEnemigo
{
	GENERATED_BODY()


public:

	AMeleeEnemigo();

	virtual void Tick(float DeltaTime) override;

protected:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
	TWeakObjectPtr<USphereComponent> SphereCollision;

	virtual void BeginPlay() override;
	
};
