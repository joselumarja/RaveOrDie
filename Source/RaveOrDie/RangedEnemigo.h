// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Enemigo.h"
#include "RangedEnemigo.generated.h"


UCLASS()
class RAVEORDIE_API ARangedEnemigo : public AEnemigo
{
	GENERATED_BODY()
	

public:
	ARangedEnemigo();

	virtual void Tick(float DeltaTime) override;

	void Shoot() override;

protected:

	virtual void BeginPlay() override;

	
	
};
