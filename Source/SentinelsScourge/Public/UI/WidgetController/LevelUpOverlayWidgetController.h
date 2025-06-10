// Copyright (c) Samarth Shroff. All Rights Reserved.
// This work is protected under applicable copyright laws in perpetuity.
// Licensed under the CC BY-NC-ND 4.0 License. See LICENSE file for details.

#pragma once

#include "CoreMinimal.h"
#include "SSCWidgetController.h"
#include "LevelUpOverlayWidgetController.generated.h"

class USSWidget;
class UAttributesMenuWidgetController;

// TODO - remove this once the level up pop up is in place. This will be replaced with
// OnAbilitySelectedDelegate with one param - ability tag. Also the OnResumeClicked will be replaced with OnAbilitySelected.
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnLevelUpResumeButtonClickedDelegate);
/**
 *
 */
UCLASS(BlueprintType, Blueprintable)
class SENTINELSSCOURGE_API ULevelUpOverlayWidgetController : public USSCWidgetController
{
	GENERATED_BODY()

private:
	UPROPERTY()
	TObjectPtr<UAttributesMenuWidgetController> AttributesMenuWidgetController;

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "UI")
	TObjectPtr<USSWidget> AttributesMenuWidget;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "UI")
	FOnLevelUpResumeButtonClickedDelegate OnResumeButtonClickedDelegate;

public:
	virtual void BindCallbacksToDependencies() override;
	virtual void BroadcastInitialValues() override;

	virtual void Initialize() override;

	TObjectPtr<UAttributesMenuWidgetController> GetAttributesMenuWidgetController(const FWidgetControllerParams &WidgetControllerParams);

	UFUNCTION(BlueprintCallable)
	void UpdateAttributesMenu(USSWidget *InAttributesMenuWidget);

	UFUNCTION(BlueprintCallable)
	void OnResumeButtonClicked();
};
