// Fill out your copyright notice in the Description page of Project Settings.

#include "A3D_Projectile.h"
#include "A3D_Ship.h"
#include "Components/CapsuleComponent.h"

#pragma region init

// Sets default values
AA3D_Ship::AA3D_Ship() {
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	MeshComponent = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("MeshComponent"));
	MeshComponent->SetSimulatePhysics(true);
	RootComponent = MeshComponent;

	SpringArmComp = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArmComp"));
	SpringArmComp->SetupAttachment(RootComponent);
	SpringArmComp->TargetArmLength = 1000.0f;
	SpringArmComp->bUsePawnControlRotation = true;
	SpringArmComp->bInheritPitch = true;
	SpringArmComp->bInheritRoll = true;
	SpringArmComp->bInheritYaw = true;
	SpringArmComp->bEnableCameraLag = true;
	SpringArmComp->bEnableCameraRotationLag = true;
	SpringArmComp->CameraLagSpeed = 5.0f;
	SpringArmComp->CameraRotationLagSpeed = 5.0f;
	SpringArmComp->CameraLagMaxDistance = 5.0f;

	CameraComp = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComponent"));
	CameraComp->SetupAttachment(SpringArmComp);

	HealthComponent = CreateDefaultSubobject<UA3D_HealthComponent>(TEXT("HealthComponent"));

	PitchRate = 50.0f;
	RollRate = 50.0f;
	YawRate = 50.0f;

	MaxSpeed = 4000.f;
	ThrustForce = 2000.0f;
	bThrusterActive = false;

	AngularDamping = 5.0f;

	MuzzleSocketName = "Muzzle";

	RateOfFire = 400.0f;

	BaseDamage = 20.0f;
	LaserSpeed = 5000.0f;
	
	HealthComponent->OnHealthChanged.AddDynamic(this, &AA3D_Ship::OnHealthChanged);

}

// Called when the game starts or when spawned
void AA3D_Ship::BeginPlay() {
	Super::BeginPlay();


	CameraComp->SetFieldOfView(DefaultFOV);
	MeshComponent->SetAngularDamping(AngularDamping);
	TimeBetweenShots = 60 / RateOfFire;
}
#pragma endregion init

// Called every frame
void AA3D_Ship::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);
	if (bThrusterActive) {
		FVector ThrustVector = GetActorForwardVector() * ThrustForce;
		MeshComponent->AddImpulse(ThrustVector);

		FVector CameraLook = CameraComp->GetForwardVector();

		FQuat NewRotation = CameraLook.ToOrientationQuat();

		FQuat Rotation = FQuat::Slerp(GetActorRotation().Quaternion(), NewRotation, DeltaTime);
		SetActorRotation(Rotation, ETeleportType::TeleportPhysics);
	}


	FVector VelocityVector = MeshComponent->GetComponentVelocity();
	auto Speed = VelocityVector.Size();
	if (!bThrusterActive) {
		CameraTurnSmoothness = 2.f;
		Speed = FMath::FInterpTo(Speed, 0.0f, GetWorld()->GetDeltaSeconds(), CameraTurnSmoothness);
	}
	MeshComponent->SetPhysicsLinearVelocity(Speed * GetActorForwardVector());

}

#pragma region Movement
void AA3D_Ship::AddPitchInput(float Value) {


	float TargetPitchSpeed = Value * PitchRate;

	MeshComponent->AddTorqueInDegrees(GetActorRightVector() * TargetPitchSpeed, NAME_None, true);
}

void AA3D_Ship::AddRollInput(float Value) {
	float TargetRollSpeed = Value * RollRate;

	if (bThrusterActive) {
		AddControllerRollInput(Value);
	} else {
		MeshComponent->AddTorqueInDegrees(GetActorForwardVector() * TargetRollSpeed, NAME_None, true);
	}
}

void AA3D_Ship::AddYawInput(float Value) {
	// Target yaw speed is based on input
	float TargetYawSpeed = Value * YawRate;

	MeshComponent->AddTorqueInDegrees(GetActorUpVector() * TargetYawSpeed, NAME_None, true);
}

void AA3D_Ship::InitiateThrust() {

	bThrusterActive = true;
}

void AA3D_Ship::StopThrust() {
	bThrusterActive = false;
}

#pragma endregion Movement

#pragma region Firing
void AA3D_Ship::StartFire() {

	float FirstDelay = LastFireTime + TimeBetweenShots - GetWorld()->TimeSeconds;
	GetWorldTimerManager().SetTimer(TimerHandle_TimeBetweenShots, this, &AA3D_Ship::Fire, TimeBetweenShots, true,
	                                FMath::Max(FirstDelay, 0.0f));
}

void AA3D_Ship::StopFire() {
	GetWorldTimerManager().ClearTimer(TimerHandle_TimeBetweenShots);
}

void AA3D_Ship::Fire() {

	if (!ProjectileClass) {
		UE_LOG(LogTemp, Warning, TEXT("ProjectileClass not defined!"))
		return;
	}

	const FVector MuzzleLocation = MeshComponent->GetSocketLocation(MuzzleSocketName);
	const FRotator MuzzleRotation = MeshComponent->GetSocketRotation(MuzzleSocketName);

	FActorSpawnParameters ActorSpawnParams;
	ActorSpawnParams.SpawnCollisionHandlingOverride =
		ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButDontSpawnIfColliding;
	ActorSpawnParams.Instigator = this;

	AA3D_Projectile* Laser = GetWorld()->SpawnActor<AA3D_Projectile>(ProjectileClass, MuzzleLocation, MuzzleRotation,
	                                                                 ActorSpawnParams);
	if (Laser) {
		auto CurrentSpeed = GetVelocity().Size() * 100;
		Laser->SetupProjectile(BaseDamage, DamageType, CurrentSpeed + LaserSpeed);
		Laser->SetOwner(this);
	}

}

#pragma endregion Firing

void AA3D_Ship::OnHealthChanged(UA3D_HealthComponent* HealthComp, float Health, float HealthDelta,
                                const UDamageType* Type, AController* InstigatedBy, AActor* DamageCauser) {


	HealthComp->SetImmunity();
	if (Health <= 0.0f && !bDead) {
		//Handle Death
		bDead = true;
		StopFire();
		MeshComponent->SetSimulatePhysics(false);
		MeshComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		DetachFromControllerPendingDestroy();

		SetLifeSpan(10.0f);
	}
}


// Called to bind functionality to input
void AA3D_Ship::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) {
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	InputComponent->BindAxis("Roll", this, &AA3D_Ship::AddRollInput);
	InputComponent->BindAxis("Pitch", this, &AA3D_Ship::AddPitchInput);
	InputComponent->BindAxis("Yaw", this, &AA3D_Ship::AddYawInput);
	InputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);
	InputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);

	InputComponent->BindAction("Fire", IE_Pressed, this, &AA3D_Ship::StartFire);
	InputComponent->BindAction("Fire", IE_Released, this, &AA3D_Ship::StopFire);

	InputComponent->BindAction("Thrust", IE_Pressed, this, &AA3D_Ship::InitiateThrust);
	InputComponent->BindAction("Thrust", IE_Released, this, &AA3D_Ship::StopThrust);


}
