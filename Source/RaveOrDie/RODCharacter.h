// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "TimerManager.h"
#include "RODCharacter.generated.h"

class AHUDManager;
class UGameManager;

UCLASS(Blueprintable)
class RAVEORDIE_API ARODCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ARODCharacter();

	/** Returns TopDownCameraComponent subobject **/
	FORCEINLINE class UCameraComponent* GetTopDownCameraComponent() const { return TopDownCameraComponent; }
	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }

	FORCEINLINE bool IsInMeleeAttack() const { return bIsInMeleeAttack; }

	FORCEINLINE bool GetCanAttack() const { return bCanAttack; }

	float GetMeleeDamage() const;

	void Attack();

	void SwapWeapon();

	void Clock();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	/** Top down camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
		class UCameraComponent* TopDownCameraComponent;

	/** Camera boom positioning the camera above the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
		class USpringArmComponent* CameraBoom;

	UPROPERTY()
		TWeakObjectPtr<UGameManager> Manager;

	UFUNCTION()
		void OnHit(AActor* SelfActor, AActor* OtherActor, FVector NormalImpulse, const FHitResult& Hit);

	void MeleeAttack();

	void DistanceAttack();

	void InitializeHUDValues();

	bool bCanAttack;

	bool bIsInMeleeAttack;

	void FinishMeleeAttack();

	void FinishDistanceAttack();

	float MAXLIFE;

	float LIFE;

	uint8 Seconds;

	uint8 Minutes;

	uint8 Hours;

	bool GunEquipped;

	TWeakObjectPtr<AHUDManager> HUDManager;

	FTimerHandle ClockTimer;
	
};
