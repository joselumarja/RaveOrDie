// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "FinalBoss.generated.h"

class UGameManager;

UCLASS()
class RAVEORDIE_API AFinalBoss : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AFinalBoss();


	~AFinalBoss();



protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION()
		void OnSeePlayer(APawn* Pawn);

	void UpdateLife(float Damage);

	UWorld* World;

	TWeakObjectPtr<ACharacter> PlayerPawn;

	FTimerHandle TimerHandle_ShotTimerExpired;

	bool bCanFire = true;

	UPROPERTY()
		TWeakObjectPtr<UGameManager> ManagerPtr;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION()
		void AddManager(UGameManager* Manager);
	
	UPROPERTY(VisibleAnywhere, Category = "AI")
		class UPawnSensingComponent* PawnSensingComp;

	UFUNCTION()
		void OnHit(AActor* SelfActor, AActor* OtherActor, FVector NormalImpulse, const FHitResult& Hit);

	UPROPERTY(EditAnywhere, Category = "AI")
		class UBehaviorTree* BehaviorTree;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
		float Health = 100.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
		float Damage = 100.f;

	void Shoot();

	void MoveToPlayer();

	float DeltaSeconds;

	float MoveSpeed;

	void ShotTimerExpired();

	float DistanceToPlayer();
};
