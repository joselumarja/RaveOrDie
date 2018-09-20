// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "TimerManager.h"
#include "TimeStruct.h"
#include "RODCharacter.generated.h"

class AHUDManager;
class USubject;

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

	UFUNCTION(BlueprintCallable)
	FORCEINLINE bool IsInMeleeAttack() const { return bIsInMeleeAttack; }

	UFUNCTION(BlueprintCallable)
	FORCEINLINE	bool GetIsDead() const { return bDead; }

	UFUNCTION(BlueprintCallable)
	FORCEINLINE	bool GetIsReloading() const { return bReloading; }

	UFUNCTION(BlueprintCallable)
	FORCEINLINE	bool GetCanDance() const { return bInactivity && !GunEquipped; }

	UFUNCTION(BlueprintCallable)
	FORCEINLINE bool GetIsGunEquipped() const { return GunEquipped; }

	FTimeStruct GetPlayTime() const;

	float GetMeleeDamage() const;

	void Attack();

	void SwapWeapon();

	void Clock();

	UPROPERTY(Category = Gameplay, EditAnywhere, BlueprintReadWrite)
		float InvulnerabilityTime;

	UPROPERTY(Category = Gameplay, EditAnywhere, BlueprintReadWrite)
		float HitInvulnerabilityTime;

	void InvulnerabilityTimerExpired();

	void HitInvulnerabilityExpired();

	void SetHitInvulnerability();

	void SetInvulnerability();

	void FinishMeleeAttack();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;

private:
	/** Top down camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
		class UCameraComponent* TopDownCameraComponent;

	/** Camera boom positioning the camera above the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
		class USpringArmComponent* CameraBoom;

	UPROPERTY(VisibleAnywhere, Category = Mesh)
		class USkeletalMeshComponent* FP_Gun;

	UFUNCTION()
	void OnHit(AActor* SelfActor, AActor* OtherActor, FVector NormalImpulse, const FHitResult& Hit);

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Stats", meta = (AllowPrivateAccess = "true"))
	bool bReloading;
	
	bool bInvulnerability = false;

	void MeleeAttack();

	void DistanceAttack();

	void InitializeHUDValues();

	void UpdateTime(FTimeStruct* TimeToUpdate);

	TWeakObjectPtr<USubject> RODCharacterSubject;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Stats", meta = (AllowPrivateAccess = "true"))
	bool bCanDistanceAttack;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Stats", meta = (AllowPrivateAccess = "true"))
	bool bIsInMeleeAttack;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Stats", meta = (AllowPrivateAccess = "true"))
	bool bDead;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Stats", meta = (AllowPrivateAccess = "true"))
	bool bInactivity;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Stats", meta = (AllowPrivateAccess = "true"))
	bool GunEquipped;

	void FinishDistanceAttack();

	void UpdateInactivity();

	void SetInactivity();

	FTimerHandle TimerHandle_InvulnerabilityHitExpired;

	FTimerHandle TimerHandle_InvulnerabilityExpired;

	float MAXLIFE;

	float LIFE;

	FTimeStruct Time;

	TWeakObjectPtr<AHUDManager> HUDManager;

	FTimerHandle ClockTimer;

	FTimerHandle InactivityTimer;

	FTimerHandle PunchingTimer;

	FTimerHandle ShotingTimer;

	UWorld* World;

};
