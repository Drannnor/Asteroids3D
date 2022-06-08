// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "A3D_HealthComponent.h"
#include "MatineeCameraShake.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/Character.h"
#include "A3D_Projectile.h"
#include "GameFramework/SpringArmComponent.h"
#include "A3D_Ship.generated.h"

class AA3D_Projectile;
UCLASS()
class ASTEROID3D_VVRTEST_API AA3D_Ship : public APawn {
	GENERATED_BODY()
	
	UPROPERTY(EditDefaultsOnly, Category = "Components")
	USkeletalMeshComponent* MeshComponent;

	UPROPERTY(EditDefaultsOnly, Category="Components")
	UCameraComponent* CameraComp;

	UPROPERTY(EditDefaultsOnly, Category="Components")
	USpringArmComponent* SpringArmComp;

	UPROPERTY(EditDefaultsOnly, Category="Components")
	UA3D_HealthComponent* HealthComponent;

	UPROPERTY(EditDefaultsOnly, Category= "FOV")
	float DefaultFOV = 65.0f;

	UPROPERTY(EditDefaultsOnly, Category= "FOV")
	float MaxFOV = 100.0f;

protected:
	//MOVEMENT
	UPROPERTY(EditDefaultsOnly, Category="Flight")
	float PitchRate;

	UPROPERTY(EditDefaultsOnly, Category="Flight")
	float RollRate;

	UPROPERTY(EditDefaultsOnly, Category="Flight")
	float YawRate;

	UPROPERTY(EditDefaultsOnly, Category="Flight")
	float AngularDamping;

	/** How quickly forward speed changes */
	UPROPERTY(EditAnywhere, Category="Flight")
	float Acceleration;

	/** Max forward speed */
	UPROPERTY(EditAnywhere, Category="Flight")
	float MaxSpeed;

	/** Min forward speed */
	UPROPERTY(EditAnywhere, Category="Flight")
	float MinSpeed;

	/** Current forward speed */
	float CurrentForwardSpeed;

	//LASERS
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category= "LASERS")
	FName MuzzleSocketName;

	//RPM BULLETS per Minute
	UPROPERTY(EditDefaultsOnly, Category= "LASERS")
	float RateOfFire;

	/** Projectile class to spawn */
	UPROPERTY(EditDefaultsOnly, Category="LASERS")
	TSubclassOf<AA3D_Projectile> ProjectileClass;

	UPROPERTY(EditDefaultsOnly, Category= "LASERS")
	USoundBase* FireSoundEffect;

	UPROPERTY(EditDefaultsOnly, Category= "LASERS")
	float BaseDamage;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="LASERS")
	TSubclassOf<UDamageType> DamageType;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="LASERS")
	float LaserSpeed;

	FTimerHandle TimerHandle_TimeBetweenShots;

	float LastFireTime;

	//Derived from rate of fire
	float TimeBetweenShots;

	UPROPERTY(BlueprintReadOnly, Category= "Player" )
	bool bDead = false;

public:
	
	//MOVEMENT
	AA3D_Ship();
	UFUNCTION()
	void AddPitchInput(float Value);
	UFUNCTION()
	void AddRollInput(float Value);
	UFUNCTION()
	void AddYawInput(float Value);
	UFUNCTION()
	void ThrustInput(float Value);
	
	//FIRING
	UFUNCTION()
	void StartFire();
	UFUNCTION()
	void StopFire();
	UFUNCTION()
	void Fire();

	//HEALTH
	UFUNCTION()
	void OnHealthChanged(UA3D_HealthComponent* HealthComp, float Health, float HealthDelta,
						 const UDamageType* Type, AController* InstigatedBy, AActor* DamageCauser);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;


	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	FQuat Euler_To_Quaternion(FRotator Current_Rotation);

};
