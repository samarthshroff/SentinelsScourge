// Copyright (c) Samarth Shroff. All Rights Reserved.
// This work is protected under applicable copyright laws in perpetuity.
// Licensed under the CC BY-NC-ND 4.0 License. See LICENSE file for details.

#include "AbilitySystem/EnemyHitGEContext.h"

void FEnemyHitGEContext::SetKnockback(const float Value)
{
	Knockback = Value;
}

float FEnemyHitGEContext::GetKnockback() const
{
	return Knockback;
}

UScriptStruct* FEnemyHitGEContext::GetScriptStruct() const
{
	return FEnemyHitGEContext::StaticStruct();
}

FGameplayEffectContext* FEnemyHitGEContext::Duplicate() const
{
	FGameplayEffectContext* NewContext = new FGameplayEffectContext(*this);
	return NewContext;
}
