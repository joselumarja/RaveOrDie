// Fill out your copyright notice in the Description page of Project Settings.

#include "Bullet.h"
#include "Enemigo.h"

// Sets default values
ABullet::ABullet()
{
	static ConstructorHelpers::FObjectFinder<UStaticMesh> ProjectileMeshAsset(TEXT("/Game/FPWeapon/Mesh/Crucifix.Crucifix"));
	ProjectileMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Bullet"));
	ProjectileMesh->SetStaticMesh(ProjectileMeshAsset.Object);

	ProjectileMesh->SetupAttachment(RootComponent);
	ProjectileMesh->BodyInstance.SetCollisionProfileName("Bullet");

	ProjectileMesh->OnComponentHit.AddDynamic(this, &ABullet::OnHit);		// set up a notification for when this component hits something
	RootComponent = ProjectileMesh;

	ProjectileMesh->bForceNavigationObstacle = true;

	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("BulletMovement"));
	ProjectileMovement->UpdatedComponent = ProjectileMesh;
	ProjectileMovement->InitialSpeed = 1200.f;
	ProjectileMovement->MaxSpeed = 1200.f;
	ProjectileMovement->bShouldBounce = false;
	ProjectileMovement->ProjectileGravityScale = 0.f; // No gravity

	Damage = 50;
}

void ABullet::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{

	if ((OtherActor != NULL) && !OtherActor->IsA(AEnemigo::StaticClass()))
	{
		
	}

	Destroy();
}


