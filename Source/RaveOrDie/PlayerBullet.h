// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Bullet.h"
#include "PlayerBullet.generated.h"


UCLASS()
class RAVEORDIE_API APlayerBullet : public ABullet
{
	GENERATED_BODY()

public:

	APlayerBullet();
	
	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

	UPROPERTY()
	TWeakObjectPtr<UParticleSystem> ExplosionParticleSystem;
	
};
