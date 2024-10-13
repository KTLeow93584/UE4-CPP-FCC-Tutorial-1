// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class UE4_CPP_Demo_FCC : ModuleRules
{
	public UE4_CPP_Demo_FCC(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "HeadMountedDisplay", "UMG" });
	}
}
