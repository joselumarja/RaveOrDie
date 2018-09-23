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

	UFUNCTION(BlueprintCallable)
	float GetMeleeDamage() const;

	void Attack();

	void SwapWeapon();

	void Clock();

	void Reload();

	void FinishMeleeAttack();

	void FinishReloading();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
		bool CanBeDamaged = true;

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

	UPROPERTY(EditAnywhere,BlueprintReadOnly, Category = Mesh, meta = (AllowPrivateAccess = "true"))
		class USkeletalMeshComponent* FP_Gun;

	FVector GunOffset;

	UFUNCTION(BlueprintCallable, Category=Life)
	void UpdateLife(float Damage);

	UFUNCTION()
	void OnHit(AActor* SelfActor, AActor* OtherActor, FVector NormalImpulse, const FHitResult& Hit);

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Stats", meta = (AllowPrivateAccess = "true"))
	bool bReloading;
	
	

	float MeleeDamage = 100.f;

	void MeleeAttack();

	void DistanceAttack();

	void InitializeHUDValues();

	void UpdateTime(FTimeStruct* TimeToUpdate);

	UPROPERTY()
	USubject* RODCharacterSubject;

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

	float MAXLIFE;

	float LIFE;

	uint8 MAXAMO;

	uint8 AMO;

	FTimeStruct Time;

	UPROPERTY()
	AHUDManager* HUDManager;

	FTimerHandle ClockTimer;

	FTimerHandle InactivityTimer;

	FTimerHandle PunchingTimer;

	FTimerHandle ShotingTimer;

	FTimerHandle ReloadingTimer;

};
