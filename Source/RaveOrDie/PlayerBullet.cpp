// Fill out your copyright notice in the Description page of Project Settings.

#include "PlayerBullet.h"


APlayerBullet::APlayerBullet() : Super()
{
	auto ProjectileMeshAsset = ConstructorHelpers::FObjectFinder<UStaticMesh>(TEXT("/Game/FPWeapon/Mesh/Amo/Crucifix.Crucifix"));

	ProjectileMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Bullet"));
	ProjectileMesh->SetStaticMesh(ProjectileMeshAsset.Object);		
	ProjectileMesh->SetupAttachment(RootComponent);
	ProjectileMesh->BodyInstance.SetCollisionProfileName("Bullet");
	ProjectileMovement->UpdatedComponent = ProjectileMesh;
	RootComponent = ProjectileMesh;
	ProjectileMovement->ProjectileGravityScale = 0.f; // No gravity
	ProjectileMesh->bForceNavigationObstacle = true;
	ProjectileMovement->bRotationFollowsVelocity = false;
	ProjectileMovement->bShouldBounce = false;
	ProjectileMovement->InitialSpeed = 1200.f;
	ProjectileMovement->MaxSpeed = 1200.f;

	ProjectileMesh->OnComponentHit.AddDynamic(this, &APlayerBullet::OnHit);
	
	auto ParticleSystemAsset = ConstructorHelpers::FObjectFinder<UParticleSystem>(TEXT("ParticleSystem'/Game/Particles/P_Explosion.P_Explosion'"));
	if (ParticleSystemAsset.Succeeded())
	{
		ExplosionParticleSystem = ParticleSystemAsset.Object;
	}

	InitialLifeSpan = 2.5f;

	Damage = 50;

}

void APlayerBullet::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ExplosionParticleSystem.Get(), GetActorLocation());
	Destroy();
}

