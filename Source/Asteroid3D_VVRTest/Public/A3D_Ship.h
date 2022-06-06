// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/Character.h"
#include "GameFramework/SpringArmComponent.h"
#include "A3D_Ship.generated.h"

UCLASS()
class ASTEROID3D_VVRTEST_API AA3D_Ship : public ACharacter {
	GENERATED_BODY()


	UPROPERTY(EditDefaultsOnly, Category= "FOV")
	float DefaultFOV = 65.0f;

	UPROPERTY(EditDefaultsOnly, Category= "FOV")
	float MaxFOV = 100.0f;
	

	UPROPERTY(VisibleAnywhere, Category="Components")
	UCameraComponent* CameraComp;

	UPROPERTY(VisibleAnywhere, Category="Components")
	USpringArmComponent* SpringArmComp;

public:
	// Sets default values for this character's properties
	AA3D_Ship();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
