// Fill out your copyright notice in the Description page of Project Settings.

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
