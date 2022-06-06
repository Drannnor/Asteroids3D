// Fill out your copyright notice in the Description page of Project Settings.


#include "A3D_Ship.h"

// Sets default values
AA3D_Ship::AA3D_Ship() {
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	SpringArmComp = CreateDefaultSubobject<USpringArmComponent>( TEXT( "SpringArmComp" ) );
	SpringArmComp->SetupAttachment( RootComponent );
	SpringArmComp->bUsePawnControlRotation = true;
	
	CameraComp = CreateDefaultSubobject<UCameraComponent>( TEXT( "CameraComponent" ) );
	CameraComp->bUsePawnControlRotation = true;
	CameraComp->SetupAttachment( SpringArmComp );

}

// Called when the game starts or when spawned
void AA3D_Ship::BeginPlay() {
	Super::BeginPlay();
	CameraComp->SetFieldOfView( DefaultFOV );

}

// Called every frame
void AA3D_Ship::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AA3D_Ship::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) {
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	
}
