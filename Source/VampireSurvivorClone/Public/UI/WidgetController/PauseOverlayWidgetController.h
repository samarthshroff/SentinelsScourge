// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "GameplayTagContainer.h"
#include "UI/WidgetController/VSCWidgetController.h"
#include "PauseOverlayWidgetController.generated.h"

class UPlayerAttributeSet;
struct FOnAttributeChangeData;
class UWidgetTree;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FOnPlayerAttributeValueChanged, FString, Name, FString, Value, FGameplayTag, GameplayTag);

/**
 * 
 */
UCLASS(BlueprintType, Blueprintable)
class VAMPIRESURVIVORCLONE_API UPauseOverlayWidgetController : public UVSCWidgetController
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintAssignable, Category = "GAS|Attributes")
	FOnPlayerAttributeValueChanged OnPlayerAttributeValueChanged;

private:
	void AttributeChanged(const FOnAttributeChangeData& Data);
public:
	virtual void BindCallbacksToDependencies() override;
	virtual void BroadcastInitialValues() override;

	UFUNCTION(BlueprintCallable)
	void OnResumeButtonClicked();
	void GetAttributeNameAndValue(const FGameplayAttribute& Attribute, const float ValueFloat, FString& Name, FString& ValueStr) const;

	//virtual void Initialize() override;	
};



