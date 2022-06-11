// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class Asteroid3D_VVRTest : ModuleRules
{
	public Asteroid3D_VVRTest(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "GameplayCameras", "UMG" });
	}
}
