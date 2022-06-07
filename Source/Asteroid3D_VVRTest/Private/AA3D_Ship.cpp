// Fill out your copyright notice in the Description page of Project Settings.


#include "A3D_Ship.h"
#include "Components/CapsuleComponent.h"

#pragma region init
// Sets default values
AA3D_Ship::AA3D_Ship() {
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComponent"));
	MeshComponent->SetSimulatePhysics(true);
	RootComponent = MeshComponent;

	SpringArmComp = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArmComp"));
	SpringArmComp->SetupAttachment(RootComponent);
	SpringArmComp->ProbeSize = 500.0f;
	SpringArmComp->bUsePawnControlRotation = true;

	CameraComp = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComponent"));
	CameraComp->bUsePawnControlRotation = true;
	CameraComp->SetupAttachment(SpringArmComp);

	PitchRate = 50.0f;
	RollRate = 50.0f;
	YawRate = 50.0f;

	Acceleration = 500.f;
	MaxSpeed = 4000.f;
	CurrentForwardSpeed = 0.f;

	AngularDamping = 5.0f;

}

// Called when the game starts or when spawned
void AA3D_Ship::BeginPlay() {
	Super::BeginPlay();
	CameraComp->SetFieldOfView(DefaultFOV);
	MeshComponent->SetAngularDamping(AngularDamping);

}
#pragma endregion init

// Called every frame
void AA3D_Ship::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);

}

#pragma region Movement
void AA3D_Ship::AddPitchInput(float Value) {


	// Target pitch speed is based in input
	float TargetPitchSpeed = Value * PitchRate;

	// // When steering, we decrease pitch slightly
	// TargetPitchSpeed += (FMath::Abs(CurrentYawSpeed) * -0.2f);

	// Smoothly interpolate to target pitch speed
	// CurrentPitchSpeed = FMath::FInterpTo(CurrentPitchSpeed, TargetPitchSpeed, GetWorld()->GetDeltaSeconds(), 2.f);

	MeshComponent->AddTorqueInDegrees(GetActorRightVector() * TargetPitchSpeed, NAME_None, true);
}

void AA3D_Ship::AddRollInput(float Value) {
	// Target yaw speed is based on input
	float TargetRollSpeed = Value * RollRate;

	// Smoothly interpolate to target yaw speed
	// CurrentRollSpeed = FMath::FInterpTo(CurrentRollSpeed, TargetRollSpeed, GetWorld()->GetDeltaSeconds(), 2.f);

	MeshComponent->AddTorqueInDegrees(GetActorForwardVector() * TargetRollSpeed, NAME_None, true);
}

void AA3D_Ship::AddYawInput(float Value) {
	// Target yaw speed is based on input
	float TargetYawSpeed = Value * YawRate;

	// Smoothly interpolate to target yaw speed
	// CurrentYawSpeed = FMath::FInterpTo(CurrentYawSpeed, TargetYawSpeed, GetWorld()->GetDeltaSeconds(), 2.f);
	MeshComponent->AddTorqueInDegrees(GetActorUpVector() * TargetYawSpeed, NAME_None, true);
}

void AA3D_Ship::ThrustInput(float Value) {
	// Is there any input?
	bool bHasInput = !FMath::IsNearlyEqual(Value, 0.f);
	// If input is not held down, reduce speed
	float CurrentAcc = bHasInput ? (Value * Acceleration) : (-0.5f * Acceleration);
	// Calculate new speed
	float NewForwardSpeed = CurrentForwardSpeed + (GetWorld()->GetDeltaSeconds() * CurrentAcc);
	// Clamp between MinSpeed and MaxSpeed
	CurrentForwardSpeed = FMath::Clamp(NewForwardSpeed, MinSpeed, MaxSpeed);
}

#pragma endregion Movement

#pragma region Firing
void AA3D_Ship::StartFire() {
	float FirstDelay = LastFireTime + TimeBetweenShots - GetWorld()->TimeSeconds;
	GetWorldTimerManager().SetTimer( TimerHandle_TimeBetweenShots, this, &AA3D_Ship::Fire, TimeBetweenShots, true,
									 FMath::Max( FirstDelay, 0.0f ) );
}

void AA3D_Ship::StopFire() {
}

void AA3D_Ship::Fire() {
	// GetWorld()->SpawnActor()
}

#pragma endregion Firing


// Called to bind functionality to input
void AA3D_Ship::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) {
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	InputComponent->BindAxis("Roll", this, &AA3D_Ship::AddRollInput);
	InputComponent->BindAxis("Pitch", this, &AA3D_Ship::AddPitchInput);
	InputComponent->BindAxis("Yaw", this, &AA3D_Ship::AddYawInput);
	InputComponent->BindAxis("Thrust", this, &AA3D_Ship::ThrustInput);
	InputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);
	InputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);

	InputComponent->BindAction("Fire", IE_Pressed, this, &AA3D_Ship::StartFire);
	InputComponent->BindAction("Fire", IE_Released, this, &AA3D_Ship::StopFire);

}
