// Fill out your copyright notice in the Description page of Project Settings.

#include "Bullet.h"
#include "Enemigo.h"


// Sets default values
ABullet::ABullet()
{
	
}

void ABullet::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	// Only add impulse and destroy projectile if we hit a physics
	if ((OtherActor != NULL) && !OtherActor->IsA(AEnemigo::StaticClass()))
	{
		Destroy();
	}

}


