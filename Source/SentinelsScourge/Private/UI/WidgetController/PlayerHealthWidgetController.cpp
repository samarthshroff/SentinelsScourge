// Fill out your copyright notice in the Description page of Project Settings.


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
