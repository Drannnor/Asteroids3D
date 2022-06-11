// Fill out your copyright notice in the Description page of Project Settings.


#include "A3D_Asteroid.h"

#include "A3D_HealthComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AA3D_Asteroid::AA3D_Asteroid() {
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	MeshComponent->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	MeshComponent->SetSimulatePhysics(true);
	MeshComponent->SetEnableGravity(false);
	RootComponent = MeshComponent;

	HealthBarWidget = CreateDefaultSubobject<UWidgetComponent>("HealthBarComp");
	HealthBarWidget->SetWidgetSpace(EWidgetSpace::Screen);
	// HealthBarWidget->AttachToComponent(MeshComponent, FAttachmentTransformRules(EAttachmentRule::KeepRelative, EAttachmentRule::KeepRelative, EAttachmentRule::KeepWorld, false));

	HealthComponent = CreateDefaultSubobject<UA3D_HealthComponent>(TEXT("HealthComponent"));

	bDestroyed = false;
	
	HealthComponent->OnHealthChanged.AddDynamic(this, &AA3D_Asteroid::OnHealthChanged);
	MeshComponent->OnComponentHit.AddDynamic(this, &AA3D_Asteroid::OnHit);
}

void AA3D_Asteroid::BeginPlay() {
	Super::BeginPlay();


	float Scale = FMath::RandRange(1.0f, MaxScale);
	HealthComponent->SetMaxHealth(Scale * 100);
	float AsteroidScale = Scale * DefaultScale;
	MeshComponent->SetWorldScale3D(FVector(AsteroidScale));
	HealthBarWidget->SetWorldScale3D(FVector(1.0f/AsteroidScale));
	HealthBarWidget->SetRelativeLocation(FVector::UpVector);
	MeshComponent->SetPhysicsAngularVelocityInDegrees(FMath::VRand() * FMath::RandRange(-5.0f, 5.0f));
}

void AA3D_Asteroid::Tick(float DeltaSeconds) {
	Super::Tick(DeltaSeconds);
	SetActorLocation(GetActorLocation() + VelocityVector);
}


void AA3D_Asteroid::OnHealthChanged(UA3D_HealthComponent* HealthComp, float Health, float HealthDelta,
                                    const UDamageType* Type, AController* InstigatedBy, AActor* DamageCauser) {
	if (Health <= 0.0f && !bDestroyed) {
		bDestroyed = true;
		DestroyAsteroid();
	}
}

void AA3D_Asteroid::DestroyAsteroid() {
	//TODO spawn particle effects
	Destroy();
}

void AA3D_Asteroid::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse,
			   const FHitResult& Hit) {

	//Apply Damage
	FVector HitFromDirection = OtherActor->GetActorLocation() - GetActorLocation();;
	UGameplayStatics::ApplyPointDamage(OtherActor, CollisionDamage, HitFromDirection, Hit,
	                                   nullptr, this, DamageType);
}

void AA3D_Asteroid::SetVelocityVector(FVector Velocity) {
	VelocityVector = Velocity;
}
