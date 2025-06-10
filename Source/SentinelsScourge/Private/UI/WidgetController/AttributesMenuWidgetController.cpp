// Copyright (c) Samarth Shroff. All Rights Reserved.
// This work is protected under applicable copyright laws in perpetuity.
// Licensed under the CC BY-NC-ND 4.0 License. See LICENSE file for details.

#include "UI/WidgetController/AttributesMenuWidgetController.h"

#include "AttributeSet.h"
#include "GameplayTagContainer.h"
#include "AbilitySystem/PlayerAttributeSet.h"

void UAttributesMenuWidgetController::Initialize()
{
	Super::Initialize();
}

void UAttributesMenuWidgetController::BroadcastInitialValues()
{
	Super::BroadcastInitialValues();
	for (TTuple<FGameplayTag, FGameplayAttribute(*)()>& Elem : GetPlayerAttributeSet()->AllAttributes)
	{
		FGameplayAttribute Attribute = Elem.Value();

		// 2 if conditions for Logical separation 
		if (Attribute == UPlayerAttributeSet::GetLevelAttribute() ||
			Attribute == UPlayerAttributeSet::GetXPAttribute() ||
			Attribute == UPlayerAttributeSet::GetMaxXPAttribute())
			continue;
		
		if (Attribute == GetPlayerAttributeSet()->GetHealthAttribute()) continue;
		
		FString Name;
		FString ValueStr;
		GetAttributeNameAndValue(Attribute, Attribute.GetNumericValue(PlayerAttributeSet), Name, ValueStr);
		//UE_LOG(LogTemp, Log, TEXT("UPauseOverlayWidgetController::BroadcastInitialValues Name: %s Value: %s"), *Name, *ValueStr);
		OnPlayerAttributeValueChanged.Broadcast(Name, ValueStr, Elem.Key);
	}
}

void UAttributesMenuWidgetController::BindCallbacksToDependencies()
{
	Super::BindCallbacksToDependencies();
	for (TTuple<FGameplayTag, FGameplayAttribute(*)()>& Elem : GetPlayerAttributeSet()->AllAttributes)
	{
		FGameplayAttribute Attribute = Elem.Value();
		if (Attribute == UPlayerAttributeSet::GetLevelAttribute() ||
			Attribute == UPlayerAttributeSet::GetXPAttribute() ||
			Attribute == UPlayerAttributeSet::GetMaxXPAttribute())
			continue;
		AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(Attribute).AddUObject(this, &UAttributesMenuWidgetController::AttributeChanged);
	}
}

void UAttributesMenuWidgetController::GetAttributeNameAndValue(const FGameplayAttribute& Attribute, const float ValueFloat,
															 FString& Name, FString& ValueStr) const
{
	// UE_LOG(LogTemp, Log, TEXT("UPauseOverlayWidgetController::GetAttributeNameAndValue The Attribute name %s and attribute value is:: %f "), 
	//        *(Attribute.GetName()),(ValueFloat));

	// return for now.

	float VF = ValueFloat;
	Name = Attribute.AttributeName;
	int ValueInt = static_cast<int>(ValueFloat);
	ValueStr = FString::Printf(TEXT("%d"), ValueInt);

	if (Attribute == UPlayerAttributeSet::GetMightAttribute() ||
		Attribute == UPlayerAttributeSet::GetMoveSpeedAttribute() ||		
		Attribute == UPlayerAttributeSet::GetSpeedAttribute() ||
		Attribute == UPlayerAttributeSet::GetDurationAttribute() ||
		Attribute == UPlayerAttributeSet::GetAreaAttribute() ||
		Attribute == UPlayerAttributeSet::GetCooldownAttribute() ||
		Attribute == UPlayerAttributeSet::GetLuckAttribute() ||
		Attribute == UPlayerAttributeSet::GetGrowthAttribute() ||
		Attribute == UPlayerAttributeSet::GetGreedAttribute() ||
		Attribute == UPlayerAttributeSet::GetCurseAttribute())
	{
		ValueStr = TEXT("-");
		float Result = (VF-1.0f)*100.0f;
		ValueInt = static_cast<int>(Result);
		
		if (ValueInt > 0)
		{
			ValueStr = FString::Printf(TEXT("+%d%%"), ValueInt);
		}
		else
		if (ValueInt < 0)
		{
			ValueStr = FString::Printf(TEXT("%d%%"), ValueInt);
		}
		
	}
	else
	if (Attribute == UPlayerAttributeSet::GetRecoveryAttribute())
	{
		ValueStr = FString::SanitizeFloat(ValueFloat, 2);
	}
	else
	if (Attribute != UPlayerAttributeSet::GetMaxHealthAttribute() && Attribute != UPlayerAttributeSet::GetMagnetAttribute())
	{
		if (ValueInt > 0)
		{
			ValueStr.InsertAt(0, TEXT("+"));
		}
		else
		if (ValueInt < 0)
		{
			ValueStr.InsertAt(0, TEXT("-"));
		}
	}
}

void UAttributesMenuWidgetController::AttributeChanged(const FOnAttributeChangeData& Data)
{
	FString Name;
	FString ValueStr;
	GetAttributeNameAndValue(Data.Attribute, Data.NewValue, Name, ValueStr);

	FGameplayTag Tag;
	for (TTuple<FGameplayTag, FGameplayAttribute(*)()>& Elem : GetPlayerAttributeSet()->AllAttributes)
	{
		FGameplayAttribute Attribute = Elem.Value();
		if (Data.Attribute == Attribute)
		{
			Tag = Elem.Key;
			break;
		}
	}

	OnPlayerAttributeValueChanged.Broadcast(Name, ValueStr, Tag);
}


