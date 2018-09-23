// Fill out your copyright notice in the Description page of Project Settings.

#include "VeryBigBullet.h"

AVeryBigBullet::AVeryBigBullet() : Super()
{
	static ConstructorHelpers::FObjectFinder<UStaticMesh> ProjectileMeshAsset(TEXT("/Game/FPWeapon/Mesh/Amo/Botijo.Botijo"));
	ProjectileMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Bullet"));
	ProjectileMesh->SetStaticMesh(ProjectileMeshAsset.Object);

	ProjectileMesh->SetupAttachment(RootComponent);
	ProjectileMesh->BodyInstance.SetCollisionProfileName("Bullet");
	ProjectileMovement->UpdatedComponent = ProjectileMesh;
	ProjectileMesh->OnComponentHit.AddDynamic(this, &ABullet::OnHit);		// set up a notification for when this component hits something
	RootComponent = ProjectileMesh;
	ProjectileMovement->InitialSpeed = 700.f;
	ProjectileMovement->MaxSpeed = 700.f;
	ProjectileMovement->ProjectileGravityScale = 1.f;
	ProjectileMesh->bForceNavigationObstacle = true;
	ProjectileMovement->bRotationFollowsVelocity = true;
	ProjectileMovement->bShouldBounce = true;

	InitialLifeSpan = 2.f;

	Damage = 75;
}

