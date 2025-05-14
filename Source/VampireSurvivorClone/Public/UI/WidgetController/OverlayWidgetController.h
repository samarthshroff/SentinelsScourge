// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayEffectTypes.h"
#include "UI/WidgetController/VSCWidgetController.h"
#include "OverlayWidgetController.generated.h"

class UPauseOverlayWidgetController;
class UVSWidget;

// This may slow doen the game as this is going to be too frequently broadcasted.
// One way is to access the XP data directly but I will go with this method first.
// Will change if it really slows down the game.
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnHeroXPChangedDelegate, float, NewXP);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnHeroMaxXPChangedDelegate, float, NewMaxXP);

/**
 * 
 */
UCLASS(BlueprintType, Blueprintable)
class VAMPIRESURVIVORCLONE_API UOverlayWidgetController : public UVSCWidgetController
{
	GENERATED_BODY()
private:
	UPROPERTY()
	TObjectPtr<UVSWidget> PauseOverlayWidget;

	UPROPERTY()
	TSubclassOf<UVSWidget> PauseOverlayWidgetClass;

	UPROPERTY()
	TObjectPtr<UPauseOverlayWidgetController> PauseOverlayWidgetController;

public:
	UPROPERTY(BlueprintAssignable, Category = "GAS|Attributes")
	FOnHeroXPChangedDelegate OnHeroXPChanged;

	UPROPERTY(BlueprintAssignable, Category = "GAS|Attributes")
	FOnHeroMaxXPChangedDelegate OnHeroMaxXPChanged;

public:
	void SetPauseOverlayWidget(TSubclassOf<UVSWidget> InPauseOverlayWidgetClass);
	virtual void BroadcastInitialValues() override;

	UFUNCTION(BlueprintCallable)
	void OnPauseButtonClicked();

	TObjectPtr<UPauseOverlayWidgetController> GetPauseWidgetController(const FWidgetControllerParams& WidgetControllerParams);

	void HeroXPChanged(const FOnAttributeChangeData& Data);
	void HeroMaxXPChanged(const FOnAttributeChangeData& Data);
	virtual void BindCallbacksToDependencies() override;
	
};
