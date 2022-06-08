// Fill out your copyright notice in the Description page of Project Settings.


#include "A3D_Asteroid.h"

#include "A3D_HealthComponent.h"

// Sets default values
AA3D_Asteroid::AA3D_Asteroid() {
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	MeshComponent->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	MeshComponent->SetSimulatePhysics(true);
	MeshComponent->SetEnableGravity(false);
	RootComponent = MeshComponent;

	HealthComponent = CreateDefaultSubobject<UA3D_HealthComponent>( TEXT( "HealthComponent" ) );
	HealthComponent->OnHealthChanged.AddDynamic( this, &AA3D_Asteroid::OnHealthChanged );

	bDestroyed = false;
}


void AA3D_Asteroid::OnHealthChanged(UA3D_HealthComponent* HealthComp, float Health, float HealthDelta,
	const UDamageType* DamageType, AController* InstigatedBy, AActor* DamageCauser) {
	if(Health <= 0.0f && !bDestroyed) {
		bDestroyed = true;
		//TODO destroy
		if(GEngine) GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Red, "Asteroid Destroyed");
	}
}


