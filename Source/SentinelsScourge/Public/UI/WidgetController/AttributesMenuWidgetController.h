// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "UI/WidgetController/SSCWidgetController.h"
#include "AttributesMenuWidgetController.generated.h"

struct FOnAttributeChangeData;
struct FGameplayAttribute;
DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FOnPlayerAttributeValueChanged, FString, Name, FString, Value, FGameplayTag, GameplayTag);

/**
 *
 */
UCLASS(BlueprintType, Blueprintable)
class SENTINELSSCOURGE_API UAttributesMenuWidgetController : public USSCWidgetController
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintAssignable, Category = "GAS|Attributes")
	FOnPlayerAttributeValueChanged OnPlayerAttributeValueChanged;

public:
	virtual void BroadcastInitialValues() override;
	virtual void BindCallbacksToDependencies() override;
	virtual void Initialize() override;

private:
	void GetAttributeNameAndValue(const FGameplayAttribute &Attribute, const float ValueFloat,
								  FString &Name, FString &ValueStr) const;

	void AttributeChanged(const FOnAttributeChangeData &Data);
};
