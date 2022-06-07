// Fill out your copyright notice in the Description page of Project Settings.


#include "A3D_PlayerController.h"

#include "A3D_Ship.h"

AA3D_PlayerController::AA3D_PlayerController() {
	// bAutoManageActiveCameraTarget = false;
}

void AA3D_PlayerController::SetupInputComponent() {
	Super::SetupInputComponent();

	// AA3D_Ship* character = Cast<AA3D_Ship>(GetPawn());
	// if (character != NULL) {
	// 	InputComponent->BindAxis("Roll", character, &AA3D_Ship::AddRollInput);
	//
	// } else {
	// 	UE_LOG(LogTemp, Warning, TEXT("character no found"))
	// }
	//
	// InputComponent->BindAxis("Pitch", this, &AA3D_PlayerController::AddPitchInput);
	// InputComponent->BindAxis("Yaw", this, &AA3D_PlayerController::AddYawInput);
}
