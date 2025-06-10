// Copyright (c) Samarth Shroff. All Rights Reserved.
// This work is protected under applicable copyright laws in perpetuity.
// Licensed under the CC BY-NC-ND 4.0 License. See LICENSE file for details.

#include "UI/WidgetController/PlayerHealthWidgetController.h"

#include "AbilitySystem/PlayerAttributeSet.h"

void UPlayerHealthWidgetController::BroadcastInitialValues()
{
	Super::BroadcastInitialValues();

	OnHealthChanged.Broadcast(GetPlayerAttributeSet()->GetHealth());
	OnMaxHealthChanged.Broadcast(GetPlayerAttributeSet()->GetMaxHealth());
}

void UPlayerHealthWidgetController::BindCallbacksToDependencies()
{
	Super::BindCallbacksToDependencies();
	
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(
		GetPlayerAttributeSet()->GetHealthAttribute()).AddUObject(this, &UPlayerHealthWidgetController::HealthChanged);

	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(
		GetPlayerAttributeSet()->GetMaxHealthAttribute()).AddUObject(this, &UPlayerHealthWidgetController::MaxHealthChanged);
}

void UPlayerHealthWidgetController::HealthChanged(const FOnAttributeChangeData& Data) const
{
	OnHealthChanged.Broadcast(Data.NewValue);
}

void UPlayerHealthWidgetController::MaxHealthChanged(const FOnAttributeChangeData& Data) const
{
	OnMaxHealthChanged.Broadcast(Data.NewValue);
}
