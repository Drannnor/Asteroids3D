// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/Actor.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "A3D_Projectile.generated.h"

UCLASS()
class ASTEROID3D_VVRTEST_API AA3D_Projectile : public AActor {
	GENERATED_BODY()

	/** Sphere collision component */
	UPROPERTY(EditAnywhere, Category= "Projectile")
	UCapsuleComponent* CollisionComp;

	UPROPERTY(EditDefaultsOnly, Category="Projectile")
	UStaticMeshComponent* MeshComponent;

	/** Projectile movement component */
	UPROPERTY(EditDefaultsOnly, Category = "Projectile")
	UProjectileMovementComponent* ProjectileMovement;


public:
	// Sets default values for this actor's properties
	AA3D_Projectile();


	/** called when projectile hits something */
	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse,
	           const FHitResult& Hit);

	
	
	void SetupProjectile(float BaseDamage, const TSubclassOf<UDamageType>& Class, float LaserSpeed);


protected:
	float Damage;
	TSubclassOf<UDamageType> DamageType;

	void DestroyProjectile();

	virtual void BeginPlay() override;
};
