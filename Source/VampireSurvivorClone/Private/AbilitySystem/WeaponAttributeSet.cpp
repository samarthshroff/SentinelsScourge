// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/WeaponAttributeSet.h"

#include "GameplayEffectExtension.h"

float UWeaponAttributeSet::ClampInclusive(float Value, float Min, float Max)
{
	if (Value < Min) return Min;
	if (Value > Max) return Max;
	return Value;
}

void UWeaponAttributeSet::PostGameplayEffectExecute(const struct FGameplayEffectModCallbackData& Data)
{
	Super::PostGameplayEffectExecute(Data);

	if (Data.EvaluatedData.Attribute == GetLevelAttribute())
	{
		SetLevel(ClampInclusive(GetLevel(), 0.0f, GetMaxLevel()));
	}
	if (Data.EvaluatedData.Attribute == GetDamageAttribute())
	{
		SetDamage(ClampInclusive(GetDamage(), 0.0f, GetMaxDamage()));
	}
	if (Data.EvaluatedData.Attribute == GetAreaAttribute())
	{
		SetArea(ClampInclusive(GetArea(), 0.0f, GetMaxArea()));
	}
	if (Data.EvaluatedData.Attribute == GetDurationAttribute())
	{
		SetDuration(ClampInclusive(GetDuration(), 0.0f, GetMaxDuration()));
	}
	if (Data.EvaluatedData.Attribute == GetPierceAttribute())
	{
		SetPierce(ClampInclusive(GetPierce(), 0.0f, GetMaxPierce()));
	}
	if (Data.EvaluatedData.Attribute == GetSpeedAttribute())
	{
		SetSpeed(ClampInclusive(GetSpeed(), 0.0f, GetMaxSpeed()));
	}
	if (Data.EvaluatedData.Attribute == GetChanceAttribute())
	{
		SetChance(ClampInclusive(GetChance(), 0.0f, GetMaxChance()));
	}
	if (Data.EvaluatedData.Attribute == GetAmountAttribute())
	{
		SetAmount(ClampInclusive(GetAmount(), 0.0f, GetPoolLimit()));
	}
}

void UWeaponAttributeSet::PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue)
{
	Super::PreAttributeChange(Attribute, NewValue);

	if (Attribute == GetLevelAttribute())
	{
		NewValue = ClampInclusive(NewValue, 0.0f, GetMaxLevel());
	}
	if (Attribute == GetDamageAttribute())
	{
		NewValue = ClampInclusive(NewValue, 0.0f, GetMaxDamage());
	}
	if (Attribute == GetAreaAttribute())
	{
		NewValue = ClampInclusive(NewValue, 0.0f, GetMaxArea());
	}
	if (Attribute == GetDurationAttribute())
	{
		NewValue = ClampInclusive(NewValue, 0.0f, GetMaxDuration());
	}	
	if (Attribute == GetPierceAttribute())
	{
		NewValue = ClampInclusive(NewValue, 0.0f, GetPierce());
	}
	if (Attribute == GetSpeedAttribute())
	{
		NewValue = ClampInclusive(NewValue, 0.0f, GetMaxSpeed());
	}	
	if (Attribute == GetChanceAttribute())
	{
		NewValue = ClampInclusive(NewValue, 0.0f, GetChance());
	}	
	if (Attribute == GetAmountAttribute())
	{
		NewValue = ClampInclusive(NewValue, 0.0f, GetPoolLimit());
	}
}
