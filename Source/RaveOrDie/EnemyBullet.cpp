// Fill out your copyright notice in the Description page of Project Settings.

#include "EnemyBullet.h"

AEnemyBullet::AEnemyBullet() : Super()
{
	static ConstructorHelpers::FObjectFinder<UStaticMesh> ProjectileMeshAsset(TEXT("/Game/FPWeapon/Mesh/Amo/Cola.Cola"));
	ProjectileMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Bullet"));
	ProjectileMesh->SetStaticMesh(ProjectileMeshAsset.Object);

	ProjectileMesh->SetupAttachment(RootComponent);
	ProjectileMesh->BodyInstance.SetCollisionProfileName("Bullet");
	ProjectileMovement->UpdatedComponent = ProjectileMesh;
	ProjectileMesh->OnComponentHit.AddDynamic(this, &ABullet::OnHit);		// set up a notification for when this component hits something
	RootComponent = ProjectileMesh;
	ProjectileMovement->InitialSpeed = 800.f;
	ProjectileMovement->MaxSpeed = 800.f;
	ProjectileMovement->ProjectileGravityScale = 0.8f; 
	ProjectileMesh->bForceNavigationObstacle = true;
	ProjectileMovement->bRotationFollowsVelocity = true;
	ProjectileMovement->bShouldBounce = true;

	InitialLifeSpan = 1.5f;

	Damage = 25;

}
