// Fill out your copyright notice in the Description page of Project Settings.


#include "A3D_PlayerController.h"

AA3D_PlayerController::AA3D_PlayerController() {

}

void AA3D_PlayerController::SetupInputComponent() {
	Super::SetupInputComponent();
	
	InputComponent->BindAxis("Roll", this, &AA3D_PlayerController::AddRollInput);
	InputComponent->BindAxis("Pitch", this, &AA3D_PlayerController::AddPitchInput);
	InputComponent->BindAxis("Yaw", this, &AA3D_PlayerController::AddYawInput);
}
