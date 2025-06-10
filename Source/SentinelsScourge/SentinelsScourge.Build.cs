// Copyright (c) Samarth Shroff. All Rights Reserved.
// This work is protected under applicable copyright laws in perpetuity.
// Licensed under the CC BY-NC-ND 4.0 License. See LICENSE file for details.

using UnrealBuildTool;
using System.IO;

public class SentinelsScourge : ModuleRules
{
	public SentinelsScourge(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
	
		PublicDependencyModuleNames.AddRange(new string[] 
		                                     {
			                                     "Core", "CoreUObject", "Engine", "InputCore", "EnhancedInput", "GameplayAbilities", "Niagara" 
		                                     });

		PrivateDependencyModuleNames.AddRange(new string[] 
		{
			"AIModule", "GameplayTags", "GameplayTasks", "NavigationSystem"
			
		});
		
		PublicIncludePaths.Add(Path.Combine(ModuleDirectory, "Public"));

		// Uncomment if you are using Slate UI
		// PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });
		
		// Uncomment if you are using online features
		// PrivateDependencyModuleNames.Add("OnlineSubsystem");

		// To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
	}
}
