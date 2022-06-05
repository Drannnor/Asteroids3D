// Copyright Epic Games, Inc. All Rights Reserved.

#include "Asteroid3D_VVRTestGameMode.h"
#include "Asteroid3D_VVRTestPawn.h"

AAsteroid3D_VVRTestGameMode::AAsteroid3D_VVRTestGameMode()
{
	// set default pawn class to our flying pawn
	DefaultPawnClass = AAsteroid3D_VVRTestPawn::StaticClass();
}
