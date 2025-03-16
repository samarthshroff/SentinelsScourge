// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class VampireSurvivorClone : ModuleRules
{
	public VampireSurvivorClone(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
	
		PublicDependencyModuleNames.AddRange(new string[] { "AIModule", "Core", "CoreUObject", "Engine", "InputCore", "EnhancedInput", "GameplayTags" });

		PrivateDependencyModuleNames.AddRange(new string[] {"AIModule"});

		// Uncomment if you are using Slate UI
		// PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });
		
		// Uncomment if you are using online features
		// PrivateDependencyModuleNames.Add("OnlineSubsystem");

		// To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
	}
}
