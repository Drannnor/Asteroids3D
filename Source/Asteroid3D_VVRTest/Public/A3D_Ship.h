// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MatineeCameraShake.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/Character.h"
#include "GameFramework/SpringArmComponent.h"
#include "A3D_Ship.generated.h"

UCLASS()
class ASTEROID3D_VVRTEST_API AA3D_Ship : public APawn {
	GENERATED_BODY()
	/** StaticMesh component that will be the visuals for our flying pawn */
	UPROPERTY(Category = Mesh, VisibleDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* MeshComponent;

	UPROPERTY(VisibleAnywhere, Category="Components")
	UCameraComponent* CameraComp;

	UPROPERTY(VisibleAnywhere, Category="Components")
	USpringArmComponent* SpringArmComp;

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
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category= "LASERS")
	UParticleSystem* MuzzleEffect;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category= "LASERS")
	FName MuzzleSocketName;

	UPROPERTY(EditDefaultsOnly, Category= "LASERS")
	USoundBase* FireSoundEffect;

	UPROPERTY(EditDefaultsOnly, Category= "LASERS")
	float BaseDamage;

	//RPM BULLETS per Minute
	UPROPERTY(EditDefaultsOnly, Category= "Weapon")
	float RateOfFire;

	FTimerHandle TimerHandle_TimeBetweenShots;

	float LastFireTime;

	//Derived from rate of fire
	float TimeBetweenShots;


	

public:
	// Sets default values for this character's properties
	AA3D_Ship();
	UFUNCTION()
	void AddPitchInput(float Value);
	UFUNCTION()
	void AddRollInput(float Value);
	UFUNCTION()
	void AddYawInput(float Value);
	UFUNCTION()
	void ThrustInput(float Value);
	UFUNCTION()
	void StartFire();
	UFUNCTION()
	void StopFire();
	UFUNCTION()
	void Fire();

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
