// Copyright (c) Samarth Shroff. All Rights Reserved.
// This work is protected under applicable copyright laws in perpetuity.
// Licensed under the CC BY-NC-ND 4.0 License. See LICENSE file for details.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "SSAbilitySystemLibrary.generated.h"

class UAttributesMenuWidgetController;
struct FGameplayTag;
class ASSHUD;
struct FWidgetControllerParams;
class UPauseOverlayWidgetController;
class UOverlayWidgetController;

/**
 * Ability System related Blueprint function library.
 */
UCLASS()
class SENTINELSSCOURGE_API USSAbilitySystemLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	// Essential Object references required by the UI code are given out in the OutWidgetControllerParams and OutHUD.
	UFUNCTION(BlueprintPure, Category = "SS Ability System | WidgetController", meta = (WorldContext = "WorldContextObject", DefaultToSelf = "WorldContextObject"))
	static bool MakeWidgetControllerParams(const UObject *WorldContextObject, FWidgetControllerParams &OutWidgetControllerParams, ASSHUD *&OutHUD);

	// Gets the main Overlay widget controller.
	UFUNCTION(BlueprintPure, Category = "SS Ability System | WidgetController", meta = (WorldContext = "WorldContextObject", DefaultToSelf = "WorldContextObject"))
	static UOverlayWidgetController *GetOverlayWidgetController(const UObject *WorldContextObject);

	// Gets the Pause menu overlay widget controller.
	UFUNCTION(BlueprintPure, Category = "SS Ability System | WidgetController", meta = (WorldContext = "WorldContextObject", DefaultToSelf = "WorldContextObject"))
	static UPauseOverlayWidgetController *GetPauseOverlayWidgetController(const UObject *WorldContextObject);

	// Gets the Pause menu overlay widget controller.
	UFUNCTION(BlueprintPure, Category = "SS Ability System | WidgetController", meta = (WorldContext = "WorldContextObject", DefaultToSelf = "WorldContextObject"))
	static UAttributesMenuWidgetController *GetAttributesMenuWidgetController(const UObject *WorldContextObject);

	// Gets all the gameplay tags from this project. Used by the python script to generate Weapon AttributeSet .h and .cpp for each tag under "Weapon.Hero"
	UFUNCTION(BlueprintCallable, Category = "Ability System | Python")
	static TArray<FGameplayTag> GetAllGameplayTagsThatMatch(const FString &MatchString);
};
