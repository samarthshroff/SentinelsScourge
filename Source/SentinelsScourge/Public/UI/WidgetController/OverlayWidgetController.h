// Copyright (c) Samarth Shroff. All Rights Reserved.
// This work is protected under applicable copyright laws in perpetuity.
// Licensed under the CC BY-NC-ND 4.0 License. See LICENSE file for details.

#pragma once

#include "CoreMinimal.h"
#include "GameplayEffectTypes.h"
#include "UI/WidgetController/SSCWidgetController.h"
#include "OverlayWidgetController.generated.h"

class ULevelUpOverlayWidgetController;
class UPauseOverlayWidgetController;
class USSWidget;

// This may slow doen the game as this is going to be too frequently broadcasted.
// One way is to access the XP data directly but I will go with this method first.
// Will change if it really slows down the game.
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnHeroXPChangedDelegate, float, NewXP);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnHeroMaxXPChangedDelegate, float, NewMaxXP);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnLevelUpOverlayFocusChangedDelegate, bool, bIsShown);

UENUM(BlueprintType)
enum class ECurrentlyShowingMenu : uint8
{
	None UMETA(DisplayName = "None"),
	PauseMenu UMETA(DisplayName = "PauseMenu"),
	LevelUpMenu UMETA(DisplayName = "LevelUpMenu"),
};

/**
 *
 */
UCLASS(BlueprintType, Blueprintable)
class SENTINELSSCOURGE_API UOverlayWidgetController : public USSCWidgetController
{
	GENERATED_BODY()
private:
	UPROPERTY()
	TObjectPtr<USSWidget> PauseOverlayWidget;

	UPROPERTY()
	TSubclassOf<USSWidget> PauseOverlayWidgetClass;

	UPROPERTY()
	TObjectPtr<UPauseOverlayWidgetController> PauseOverlayWidgetController;

	UPROPERTY()
	TObjectPtr<USSWidget> LevelUpOverlayWidget;

	UPROPERTY()
	TSubclassOf<USSWidget> LevelUpOverlayWidgetClass;

	UPROPERTY()
	TObjectPtr<ULevelUpOverlayWidgetController> LevelUpOverlayWidgetController;

	ECurrentlyShowingMenu CurrentlyShowing;

public:
	UPROPERTY(BlueprintAssignable, Category = "GAS|Attributes")
	FOnHeroXPChangedDelegate OnHeroXPChanged;

	UPROPERTY(BlueprintAssignable, Category = "GAS|Attributes")
	FOnHeroMaxXPChangedDelegate OnHeroMaxXPChanged;

	UPROPERTY(BlueprintAssignable, Category = "GAS|Attributes")
	FOnLevelUpOverlayFocusChangedDelegate LevelUpOverlayFocusChanged;

private:
	UFUNCTION()
	void OnPauseMenuResumeButtonClicked();

	UFUNCTION()
	void OnLevelUpResumeButtonClicked();

public:
	void SetOtherOverlayWidgets(TSubclassOf<USSWidget> InPauseOverlayWidgetClass, TSubclassOf<USSWidget> InLevelUpOverlayWidgetClass);
	virtual void BroadcastInitialValues() override;

	UFUNCTION(BlueprintCallable)
	void OnPauseButtonClicked();

	TObjectPtr<UPauseOverlayWidgetController> GetPauseWidgetController(const FWidgetControllerParams &WidgetControllerParams);
	TObjectPtr<ULevelUpOverlayWidgetController> GetLevelUpOverlayWidgetController(const FWidgetControllerParams &WidgetControllerParams);

	void HeroXPChanged(const FOnAttributeChangeData &Data);
	void HeroMaxXPChanged(const FOnAttributeChangeData &Data);
	void HeroLevelChanged(const FOnAttributeChangeData &Data);
	virtual void BindCallbacksToDependencies() override;
	virtual void Initialize() override;

	UFUNCTION(BlueprintCallable)
	ECurrentlyShowingMenu GetCurrentlyShowingMenu();

	friend class USSAbilitySystemLibrary;
};
