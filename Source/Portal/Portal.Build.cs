// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class Portal : ModuleRules
{
	public Portal(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[]
		{
			"Core", "CoreUObject", "Engine", "InputCore", "EnhancedInput",
			"PhysicsCore"
		});
		
		PrivateDependencyModuleNames.AddRange(new string [] {
			"UnrealEd",				
			
		});

		PrivateIncludePaths.Add(ModuleDirectory);
		PublicIncludePaths.Add(ModuleDirectory);
	}
}
