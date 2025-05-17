// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "VSCWidgetController.h"
#include "LevelUpOverlayWidgetController.generated.h"

class UVSWidget;
class UAttributesMenuWidgetController;

// TODO - remove this once the level up pop up is in place. This will be replaced with
// OnAbilitySelectedDelegate with one param - ability tag. Also the OnResumeClicked will be replaced with OnAbilitySelected.
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnLevelUpResumeButtonClickedDelegate);
/**
 * 
 */
UCLASS(BlueprintType, Blueprintable)
class VAMPIRESURVIVORCLONE_API ULevelUpOverlayWidgetController : public UVSCWidgetController
{
	GENERATED_BODY()

private:
	UPROPERTY()
	TObjectPtr<UAttributesMenuWidgetController> AttributesMenuWidgetController;

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "UI")
	TObjectPtr<UVSWidget> AttributesMenuWidget;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "UI")
	FOnLevelUpResumeButtonClickedDelegate OnResumeButtonClickedDelegate;
	
public:
	virtual void BindCallbacksToDependencies() override;
	virtual void BroadcastInitialValues() override;

	virtual void Initialize() override;
	
	TObjectPtr<UAttributesMenuWidgetController> GetAttributesMenuWidgetController(const FWidgetControllerParams& WidgetControllerParams);

	UFUNCTION(BlueprintCallable)
	void UpdateAttributesMenu(UVSWidget* InAttributesMenuWidget);

	UFUNCTION(BlueprintCallable)
	void OnResumeButtonClicked();
};
