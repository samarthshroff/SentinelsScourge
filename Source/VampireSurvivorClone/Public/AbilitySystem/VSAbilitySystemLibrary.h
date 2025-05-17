// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "VSAbilitySystemLibrary.generated.h"

class UAttributesMenuWidgetController;
struct FGameplayTag;
class AVSHUD;
struct FWidgetControllerParams;
class UPauseOverlayWidgetController;
class UOverlayWidgetController;

/**
 * Ability System related Blueprint function library.
 */
UCLASS()
class VAMPIRESURVIVORCLONE_API UVSAbilitySystemLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	// Essential Object references required by the UI code are given out in the OutWidgetControllerParams and OutHUD.
	UFUNCTION(BlueprintPure, Category = "VS Ability System | WidgetController", meta = (WorldContext = "WorldContextObject", DefaultToSelf = "WorldContextObject"))
	static bool MakeWidgetControllerParams(const UObject* WorldContextObject, FWidgetControllerParams& OutWidgetControllerParams, AVSHUD*& OutHUD);

	// Gets the main Overlay widget controller.
	UFUNCTION(BlueprintPure, Category = "VS Ability System | WidgetController", meta = (WorldContext = "WorldContextObject", DefaultToSelf = "WorldContextObject"))
	static UOverlayWidgetController* GetOverlayWidgetController(const UObject* WorldContextObject);

	// Gets the Pause menu overlay widget controller.
	UFUNCTION(BlueprintPure, Category = "VS Ability System | WidgetController", meta = (WorldContext = "WorldContextObject", DefaultToSelf = "WorldContextObject"))
	static UPauseOverlayWidgetController* GetPauseOverlayWidgetController(const UObject* WorldContextObject);

	// Gets the Pause menu overlay widget controller.
	UFUNCTION(BlueprintPure, Category = "VS Ability System | WidgetController", meta = (WorldContext = "WorldContextObject", DefaultToSelf = "WorldContextObject"))
	static UAttributesMenuWidgetController* GetAttributesMenuWidgetController(const UObject* WorldContextObject);

	// Gets all the gameplay tags from this project. Used by the python script to generate Weapon AttributeSet .h and .cpp for each tag under "Weapon.Hero"
	UFUNCTION(BlueprintCallable, Category="Ability System | Python")
	static TArray<FGameplayTag> GetAllGameplayTagsThatMatch(const FString& MatchString);	
};
