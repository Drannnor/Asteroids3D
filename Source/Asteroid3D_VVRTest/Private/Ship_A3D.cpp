// Fill out your copyright notice in the Description page of Project Settings.


#include "Ship_A3D.h"

// Sets default values
AShip_A3D::AShip_A3D()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AShip_A3D::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AShip_A3D::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AShip_A3D::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

