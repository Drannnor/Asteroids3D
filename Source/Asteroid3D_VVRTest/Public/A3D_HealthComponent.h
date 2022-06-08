#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "A3D_HealthComponent.generated.h"


UCLASS()
class ASTEROID3D_VVRTEST_API UA3D_HealthComponent : public UActorComponent {
	GENERATED_BODY()

	DECLARE_DYNAMIC_MULTICAST_DELEGATE_SixParams( FOnHealthChangedSignature, UA3D_HealthComponent*, HealthComp, float,
												  Health, float, HealthDelta, const class UDamageType*, DamageType,
												  class AController*, InstigatedBy, AActor*, DamageCauser );


public:
	// Sets default values for this component's properties
	UA3D_HealthComponent();

protected:

	UPROPERTY(BlueprintReadOnly, Category = "HealthComponent")
	float Health;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "HealthComponent")
	float MaxHealth = 100;

	bool bIsDead;
	// Called when the game starts
	virtual void BeginPlay() override;

	UFUNCTION()
	void HandleTakeAnyDamage( AActor* DamagedActor, float Damage, const class UDamageType* DamageType,
							  class AController* InstigatedBy, AActor* DamageCauser );


public:

	float GetHealth() const;

	UFUNCTION(BlueprintCallable, Category="HealthComponents" )
	void Heal( float HealAmount );

	UPROPERTY( BlueprintAssignable, Category = "Events" )
	FOnHealthChangedSignature OnHealthChanged;
};