// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Enemigo.h"
#include "MeleeEnemigo.generated.h"


UCLASS()
class RAVEORDIE_API AMeleeEnemigo : public AEnemigo
{
	GENERATED_BODY()


public:

	AMeleeEnemigo();

	virtual void Tick(float DeltaTime) override;

protected:

	virtual void BeginPlay() override;
	
};
