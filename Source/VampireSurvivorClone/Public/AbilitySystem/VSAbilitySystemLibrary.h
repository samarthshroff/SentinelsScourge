// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "VSAbilitySystemLibrary.generated.h"

struct FGameplayTag;
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
	UFUNCTION(BlueprintPure, Category = "VS Ability System | WidgetController", meta = (WorldContext = "WorldContextObject", DefaultToSelf = "WorldContextObject"))
	static bool MakeWidgetControllerParams(const UObject* WorldContextObject, FWidgetControllerParams& OutWidgetControllerParams, AVSHUD*& OutHUD);
	
	UFUNCTION(BlueprintPure, Category = "VS Ability System | WidgetController", meta = (WorldContext = "WorldContextObject", DefaultToSelf = "WorldContextObject"))
	static UOverlayWidgetController* GetOverlayWidgetController(const UObject* WorldContextObject);

	UFUNCTION(BlueprintPure, Category = "VS Ability System | WidgetController", meta = (WorldContext = "WorldContextObject", DefaultToSelf = "WorldContextObject"))
	static UPauseOverlayWidgetController* GetPauseOverlayWidgetController(const UObject* WorldContextObject);

	UFUNCTION(BlueprintCallable, Category="Ability System | Python")
	static TArray<FGameplayTag> GetAllGameplayTagsThatMatch(const FString& MatchString);	
};
