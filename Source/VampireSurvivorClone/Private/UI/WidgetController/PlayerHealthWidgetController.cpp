// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/WidgetController/PlayerHealthWidgetController.h"

#include "AbilitySystem/VSPlayerAttributeSet.h"

void UPlayerHealthWidgetController::BroadcastInitialValues()
{
	Super::BroadcastInitialValues();

	const UVSPlayerAttributeSet* PlayerAttributeSet = CastChecked<UVSPlayerAttributeSet>(AttributeSet);
	OnHealthChanged.Broadcast(PlayerAttributeSet->GetHealth());
	OnMaxHealthChanged.Broadcast(PlayerAttributeSet->GetMaxHealth());
}

void UPlayerHealthWidgetController::BindCallbacksToDependencies()
{
	Super::BindCallbacksToDependencies();

	const UVSPlayerAttributeSet* PlayerAttributeSet = CastChecked<UVSPlayerAttributeSet>(AttributeSet);
	
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(
		PlayerAttributeSet->GetHealthAttribute()).AddUObject(this, &UPlayerHealthWidgetController::HealthChanged);

	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(
		PlayerAttributeSet->GetMaxHealthAttribute()).AddUObject(this, &UPlayerHealthWidgetController::MaxHealthChanged);
}

void UPlayerHealthWidgetController::HealthChanged(const FOnAttributeChangeData& Data) const
{
	OnHealthChanged.Broadcast(Data.NewValue);
}

void UPlayerHealthWidgetController::MaxHealthChanged(const FOnAttributeChangeData& Data) const
{
	OnMaxHealthChanged.Broadcast(Data.NewValue);
}
