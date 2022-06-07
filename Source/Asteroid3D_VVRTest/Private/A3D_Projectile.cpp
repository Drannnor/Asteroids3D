// Fill out your copyright notice in the Description page of Project Settings.


#include "A3D_Projectile.h"

// Sets default values
AA3D_Projectile::AA3D_Projectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AA3D_Projectile::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AA3D_Projectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

