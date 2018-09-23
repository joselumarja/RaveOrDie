// Fill out your copyright notice in the Description page of Project Settings.

#include "Bullet.h"
#include "Enemigo.h"

// Sets default values
ABullet::ABullet()
{
	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("BulletMovement"));
}

void ABullet::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	Destroy();
}


