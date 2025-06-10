// Copyright (c) Samarth Shroff. All Rights Reserved.
// This work is protected under applicable copyright laws in perpetuity.
// Licensed under the CC BY-NC-ND 4.0 License. See LICENSE file for details.

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
