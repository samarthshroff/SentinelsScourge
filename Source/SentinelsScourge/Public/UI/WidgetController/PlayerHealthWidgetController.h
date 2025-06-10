// Copyright (c) Samarth Shroff. All Rights Reserved.
// This work is protected under applicable copyright laws in perpetuity.
// Licensed under the CC BY-NC-ND 4.0 License. See LICENSE file for details.

#pragma once

#include "CoreMinimal.h"
#include "UI/WidgetController/SSCWidgetController.h"
#include "PlayerHealthWidgetController.generated.h"

struct FOnAttributeChangeData;
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnHealthChangedDelegate, float, NewHealth);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnMaxHealthChangedDelegate, float, NewMaxHealth);

/**
 *
 */
UCLASS(BlueprintType, Blueprintable)
class SENTINELSSCOURGE_API UPlayerHealthWidgetController : public USSCWidgetController
{
	GENERATED_BODY()

public:
	virtual void BroadcastInitialValues() override;
	virtual void BindCallbacksToDependencies() override;

	UPROPERTY(BlueprintAssignable, Category = "GAS|Attributes")
	FOnHealthChangedDelegate OnHealthChanged;

	UPROPERTY(BlueprintAssignable, Category = "GAS|Attributes")
	FOnMaxHealthChangedDelegate OnMaxHealthChanged;

protected:
	void HealthChanged(const FOnAttributeChangeData &Data) const;
	void MaxHealthChanged(const FOnAttributeChangeData &Data) const;
};
