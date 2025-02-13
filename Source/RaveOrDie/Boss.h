// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Enemigo.h"
#include "Boss.generated.h"


UCLASS()
class RAVEORDIE_API ABoss : public AEnemigo
{
	GENERATED_BODY()
	
	
public:

	ABoss();

	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;

	bool bCanFire = true;

protected:

	void Shoot() override;

	
};
