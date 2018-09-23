// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "TimerManager.h"
#include "Enemigo.generated.h"

class UProgressBar;
class UUserWidget;
class UWidgetComponent;
class ARODCharacter;
class USubject;

UCLASS(Abstract)
class RAVEORDIE_API AEnemigo : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AEnemigo();

	void FinishDeadDelay();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	float DeltaSeconds;

	float MoveSpeed;

	UFUNCTION(BlueprintCallable, Category = "Hit")
	virtual void UpdateLife(float Damage);

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
	float Health;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
	float MaxHealth;

	UPROPERTY()
	USubject* EnemySubject;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
	bool CanBeDamaged = true;

	UPROPERTY()
	TWeakObjectPtr<UAnimSequence> DeadAnimation;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Stats")
	UWidgetComponent* pLifeBarWidget;

	UPROPERTY()
	TSubclassOf<UUserWidget> LifeBarWidget;

	UPROPERTY()
	TWeakObjectPtr <UProgressBar> LifeBar;

	virtual void DeadBehaviour();

public:

	TWeakObjectPtr<ARODCharacter> PlayerPawn;

	UFUNCTION()
	virtual void OnHit(AActor* SelfActor, AActor* OtherActor, FVector NormalImpulse, const FHitResult& Hit);

	/*The Component which is used for the "seeing" sense of the AI*/
	UPROPERTY(VisibleAnywhere, Category = "AI")
	class UPawnSensingComponent* PawnSensingComp;

	UPROPERTY(EditAnywhere, Category = "AI")
	class UBehaviorTree* BehaviorTree;

	UFUNCTION()
	virtual void OnSeePlayer(APawn* Pawn);

	void MoveToPlayer();

	float DistanceToPlayer();

	virtual void Shoot() PURE_VIRTUAL(AEnemigo::Shoot, );

	UFUNCTION(BlueprintCallable)
	float GetMeleeDamage() const;

	float MeleeDamage;

	FTimerHandle DeadDelay;
};
