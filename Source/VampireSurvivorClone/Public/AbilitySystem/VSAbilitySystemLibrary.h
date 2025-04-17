// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "VSAbilitySystemLibrary.generated.h"

class AVSHUD;
struct FWidgetControllerParams;
class UPauseOverlayWidgetController;
class UOverlayWidgetController;
/**
 * 
 */
UCLASS()
class VAMPIRESURVIVORCLONE_API UVSAbilitySystemLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	// Adding WorldContext =	"WorldContextObject", to meta returns a HOTRELOAD object reference.
	UFUNCTION(BlueprintPure, Category = "VS Ability System | WidgetController", meta = (DefaultToSelf = "WorldContextObject"))
	static bool MakeWidgetControllerParams(const UObject* WorldContextObject, FWidgetControllerParams& OutWidgetControllerParams, AVSHUD*& OutHUD);
	
	UFUNCTION(BlueprintPure, Category = "VS Ability System | WidgetController", meta = (DefaultToSelf = "WorldContextObject"))
	static UOverlayWidgetController* GetOverlayWidgetController(const UObject* WorldContextObject);

	UFUNCTION(BlueprintPure, Category = "VS Ability System | WidgetController", meta = (DefaultToSelf = "WorldContextObject"))
	static UPauseOverlayWidgetController* GetPauseOverlayWidgetController(const UObject* WorldContextObject);	
};
