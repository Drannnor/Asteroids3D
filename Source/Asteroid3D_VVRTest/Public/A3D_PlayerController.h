// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "A3D_PlayerController.generated.h"

/**
 * 
 */
UCLASS()
class ASTEROID3D_VVRTEST_API AA3D_PlayerController : public APlayerController
{
	GENERATED_BODY()
public:
	AA3D_PlayerController();

protected:
	 virtual void SetupInputComponent() override;
};
