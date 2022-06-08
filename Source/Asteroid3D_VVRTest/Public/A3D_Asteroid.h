// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "A3D_Asteroid.generated.h"

class UA3D_HealthComponent;
UCLASS()
class ASTEROID3D_VVRTEST_API AA3D_Asteroid : public AActor {
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, Category = "Components")
	UStaticMeshComponent* MeshComponent;

	UPROPERTY(EditDefaultsOnly, Category="Components")
	UA3D_HealthComponent* HealthComponent;

public:

	AA3D_Asteroid();
	
	UFUNCTION()
	void OnHealthChanged(UA3D_HealthComponent* HealthComp, float Health, float HealthDelta,
	                     const UDamageType* DamageType, AController* InstigatedBy, AActor* DamageCauser);
	// Sets default values for this actor's properties
protected:
	bool bDestroyed;
};
