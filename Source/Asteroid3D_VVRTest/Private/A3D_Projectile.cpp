// Fill out your copyright notice in the Description page of Project Settings.


#include "A3D_Projectile.h"
#include "Components/CapsuleComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AA3D_Projectile::AA3D_Projectile() {
	// Use a sphere as a simple collision representation
	CollisionComp = CreateDefaultSubobject<UCapsuleComponent>(TEXT("collider"));
	CollisionComp->SetCapsuleSize(20.f, 25.f, false);
	CollisionComp->SetCollisionProfileName("Projectile");
	CollisionComp->OnComponentHit.AddDynamic(this, &AA3D_Projectile::OnHit);
	CollisionComp->SetRelativeRotation(FRotator(0.0f, 0.0f, 90.0f));


	// Players can't walk on it
	CollisionComp->SetWalkableSlopeOverride(FWalkableSlopeOverride(WalkableSlope_Unwalkable, 0.f));
	CollisionComp->CanCharacterStepUpOn = ECB_No;
	
	// Set as root component
	RootComponent = CollisionComp;

	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComponent"));
	MeshComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	MeshComponent->SetRelativeScale3D(FVector(0.2f, 1.0f, 0.2f));
	MeshComponent->SetupAttachment(RootComponent);
	// Use a ProjectileMovementComponent to govern this projectile's movement
	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileComp"));
	ProjectileMovement->UpdatedComponent = CollisionComp;
	ProjectileMovement->InitialSpeed = 3000.f;
	ProjectileMovement->MaxSpeed = 3000.f;
	ProjectileMovement->bRotationFollowsVelocity = true;
	ProjectileMovement->bShouldBounce = false;

	// Die after 3 seconds by default
	InitialLifeSpan = 3.0f;

}

void AA3D_Projectile::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
                            FVector NormalImpulse, const FHitResult& Hit) {
	AActor* MyOwner = GetOwner();
	if(!MyOwner) {
		UE_LOG(LogTemp, Warning, TEXT("Projectile Owner not Defined!"))
		return;
	}

	//Apply Damage
	FVector HitFromDirection =OtherActor->GetActorLocation() - GetActorLocation();;
	UGameplayStatics::ApplyPointDamage( OtherActor, Damage, HitFromDirection, Hit,
	                                    MyOwner->GetInstigatorController(), MyOwner, DamageType);

	//TODO destroy and spawn particle effects
}

void AA3D_Projectile::SetupProjectile(float BaseDamage, const TSubclassOf<UDamageType>& type, float LaserSpeed) {
	Damage = BaseDamage;
	DamageType = type;
	ProjectileMovement->InitialSpeed = LaserSpeed;
	ProjectileMovement->MaxSpeed = LaserSpeed;
	
}
