// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Enemigo.generated.h"

class UGameManager;

UCLASS(Abstract)
class RAVEORDIE_API AEnemigo : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AEnemigo();

	~AEnemigo();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY()
	TWeakObjectPtr<UGameManager> ManagerPtr;
	
	TWeakObjectPtr<ACharacter> PlayerPawn;

	FTimerHandle TimerHandle_ShotTimerExpired; 
	
	float DeltaSeconds;

	float MoveSpeed;

	virtual void UpdateLife(float Damage);

	UWorld* World;

	bool bCanFire =true;

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
		float Health = 100.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
		float Damage = 100.f;

	UFUNCTION()
		virtual void OnHit(AActor* SelfActor, AActor* OtherActor, FVector NormalImpulse, const FHitResult& Hit);
	



	

public:

	/*The Component which is used for the "seeing" sense of the AI*/
	UPROPERTY(VisibleAnywhere, Category = "AI")
		class UPawnSensingComponent* PawnSensingComp;

	void ShotTimerExpired();

	UPROPERTY(EditAnywhere, Category = "AI")
		class UBehaviorTree* BehaviorTree;

	UFUNCTION()
		void AddManager(UGameManager* Manager);

	UFUNCTION()
		virtual void OnSeePlayer(APawn* Pawn);

	void MoveToPlayer();

	float DistanceToPlayer();

	virtual void Shoot() PURE_VIRTUAL(AEnemigo::Shoot, );
};
