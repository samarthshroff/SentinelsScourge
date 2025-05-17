// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "GameplayTagContainer.h"
#include "UI/WidgetController/VSCWidgetController.h"
#include "PauseOverlayWidgetController.generated.h"

class UAttributesMenuWidgetController;
class UVSWidget;
class UPlayerAttributeSet;
struct FOnAttributeChangeData;
class UWidgetTree;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnResumeButtonClickedDelegate);

/**
 * 
 */
UCLASS(BlueprintType, Blueprintable)
class VAMPIRESURVIVORCLONE_API UPauseOverlayWidgetController : public UVSCWidgetController
{
	GENERATED_BODY()
private:

	// UPROPERTY()
	// TSubclassOf<UVSWidget> AttributesMenuWidgetClass;

	UPROPERTY()
	TObjectPtr<UAttributesMenuWidgetController> AttributesMenuWidgetController;

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "UI")
	TObjectPtr<UVSWidget> AttributesMenuWidget;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "UI")
	FOnResumeButtonClickedDelegate OnResumeButtonClickedDelegate;
	
public:
	virtual void BindCallbacksToDependencies() override;
	virtual void BroadcastInitialValues() override;

	UFUNCTION(BlueprintCallable)
	void OnResumeButtonClicked();
	
	TObjectPtr<UAttributesMenuWidgetController> GetAttributesMenuWidgetController(const FWidgetControllerParams& WidgetControllerParams);

	virtual void Initialize() override;

	UFUNCTION(BlueprintCallable)
	void UpdateAttributesMenu(UVSWidget* InAttributesMenuWidget);
};



