// Copyright (c) Samarth Shroff. All Rights Reserved.
// This work is protected under applicable copyright laws in perpetuity.
// Licensed under the CC BY-NC-ND 4.0 License. See LICENSE file for details.

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "GameplayTagContainer.h"
#include "UI/WidgetController/SSCWidgetController.h"
#include "PauseOverlayWidgetController.generated.h"

class UAttributesMenuWidgetController;
class USSWidget;
class UPlayerAttributeSet;
struct FOnAttributeChangeData;
class UWidgetTree;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnResumeButtonClickedDelegate);

/**
 *
 */
UCLASS(BlueprintType, Blueprintable)
class SENTINELSSCOURGE_API UPauseOverlayWidgetController : public USSCWidgetController
{
	GENERATED_BODY()
private:
	// UPROPERTY()
	// TSubclassOf<USSWidget> AttributesMenuWidgetClass;

	UPROPERTY()
	TObjectPtr<UAttributesMenuWidgetController> AttributesMenuWidgetController;

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "UI")
	TObjectPtr<USSWidget> AttributesMenuWidget;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "UI")
	FOnResumeButtonClickedDelegate OnResumeButtonClickedDelegate;

public:
	virtual void BindCallbacksToDependencies() override;
	virtual void BroadcastInitialValues() override;

	UFUNCTION(BlueprintCallable)
	void OnResumeButtonClicked();

	TObjectPtr<UAttributesMenuWidgetController> GetAttributesMenuWidgetController(const FWidgetControllerParams &WidgetControllerParams);

	virtual void Initialize() override;

	UFUNCTION(BlueprintCallable)
	void UpdateAttributesMenu(USSWidget *InAttributesMenuWidget);
};
