// Fill out your copyright notice in the Description page of Project Settings.

#include "VeryBigBullet.h"

AVeryBigBullet::AVeryBigBullet() : Super()
{

	auto ProjectileMeshAsset = ConstructorHelpers::FObjectFinder<UStaticMesh>(TEXT("/Game/FPWeapon/Mesh/Amo/Botijo.Botijo"));

	ProjectileMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Bullet"));
	ProjectileMesh->SetStaticMesh(ProjectileMeshAsset.Object);
	ProjectileMesh->SetupAttachment(RootComponent);
	ProjectileMesh->BodyInstance.SetCollisionProfileName("Bullet");
	ProjectileMovement->UpdatedComponent = ProjectileMesh;
	RootComponent = ProjectileMesh;
	ProjectileMovement->InitialSpeed = 400.f;
	ProjectileMovement->MaxSpeed = 400.f;
	ProjectileMovement->ProjectileGravityScale = 1.f;
	ProjectileMesh->bForceNavigationObstacle = true;
	ProjectileMovement->bRotationFollowsVelocity = false;
	ProjectileMovement->bShouldBounce = true;


	InitialLifeSpan = 2.f;

	Damage = 75;
}

