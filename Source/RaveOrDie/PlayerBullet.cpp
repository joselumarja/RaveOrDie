// Fill out your copyright notice in the Description page of Project Settings.

#include "PlayerBullet.h"
#include "Enemigo.h"


APlayerBullet::APlayerBullet() : Super()
{
	static ConstructorHelpers::FObjectFinder<UStaticMesh> ProjectileMeshAsset(TEXT("/Game/FPWeapon/Mesh/Crucifix.Crucifix"));
	ProjectileMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Bullet"));
	ProjectileMesh->SetStaticMesh(ProjectileMeshAsset.Object);

	ProjectileMesh->SetupAttachment(RootComponent);
	ProjectileMesh->BodyInstance.SetCollisionProfileName("Bullet");

	ProjectileMesh->OnComponentHit.AddDynamic(this, &ABullet::OnHit);		// set up a notification for when this component hits something
	RootComponent = ProjectileMesh;

	ProjectileMesh->bForceNavigationObstacle = true;

	Damage = 50;


}

