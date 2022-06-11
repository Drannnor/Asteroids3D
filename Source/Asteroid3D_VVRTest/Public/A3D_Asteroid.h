// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/WidgetComponent.h"
#include "GameFramework/Actor.h"
#include "A3D_Asteroid.generated.h"

class UA3D_HealthComponent;
UCLASS()
class ASTEROID3D_VVRTEST_API AA3D_Asteroid : public AActor {
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, Category = "Components")
	UStaticMeshComponent* MeshComponent;



public:
	AA3D_Asteroid();

	UFUNCTION()
	void OnHealthChanged(UA3D_HealthComponent* HealthComp, float Health, float HealthDelta,
	                     const UDamageType* DamageType, AController* InstigatedBy, AActor* DamageCauser);

	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse,
	           const FHitResult& Hit);

	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
	UWidgetComponent* HealthBarWidget;

	UFUNCTION(BlueprintCallable)
	void SetVelocityVector(FVector Velocity);

protected:
	bool bDestroyed;

	void DestroyAsteroid();

	UPROPERTY(BlueprintReadWrite, Category="Components")
	UA3D_HealthComponent* HealthComponent;


	UPROPERTY(EditDefaultsOnly, Category="Generation")
	float MaxScale = 5.0f;

	UPROPERTY(EditDefaultsOnly, Category="Generation")
	float DefaultScale = 20.0f;


	UPROPERTY(EditDefaultsOnly, Category="Damage")
	float CollisionDamage = 30.0f;

	UPROPERTY(EditDefaultsOnly, Category="Damage")
	TSubclassOf<UDamageType> DamageType;

	FVector VelocityVector;
	
	virtual void BeginPlay() override;

	virtual void Tick(float DeltaSeconds) override;

};
