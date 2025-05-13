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
