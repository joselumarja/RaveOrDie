// Fill out your copyright notice in the Description page of Project Settings.

#include "Bullet.h"
#include "Enemigo.h"
#include "FinalBoss.h"


// Sets default values
ABullet::ABullet()
{
	static ConstructorHelpers::FObjectFinder<UStaticMesh> ProjectileMeshAsset(TEXT("/Game/Blueprints/Projectile.Projectile"));
	ProjectileMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Bullet"));
	ProjectileMesh->SetStaticMesh(ProjectileMeshAsset.Object);
	ProjectileMesh->SetupAttachment(RootComponent);
	ProjectileMesh->BodyInstance.SetCollisionProfileName("Bullet");

	ProjectileMesh->OnComponentHit.AddDynamic(this, &ABullet::OnHit);		// set up a notification for when this component hits something
	RootComponent = ProjectileMesh;

	ProjectileMesh->bForceNavigationObstacle = true;

	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("BulletMovement"));
	ProjectileMovement->UpdatedComponent = ProjectileMesh;
	ProjectileMovement->InitialSpeed = 1500.f;
	ProjectileMovement->MaxSpeed = 1500.f;
	ProjectileMovement->bRotationFollowsVelocity = true;
	ProjectileMovement->bShouldBounce = false;
	ProjectileMovement->ProjectileGravityScale = 0.f; // No gravity
}

void ABullet::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{

	if ((OtherActor != NULL) && !OtherActor->IsA(AEnemigo::StaticClass()) && !OtherActor->IsA(AFinalBoss::StaticClass()))
	{
		Destroy();
	}

}


