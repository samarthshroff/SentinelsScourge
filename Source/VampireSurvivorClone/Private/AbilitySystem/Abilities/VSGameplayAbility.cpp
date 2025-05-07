// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/Abilities/VSGameplayAbility.h"


FOnAbilityCooldownComplete UVSGameplayAbility::OnAbilityCooldownCompleteDelegate;

void UVSGameplayAbility::Initialize(float InCooldown, UAbilitySystemComponent* InAbilitySystemComponent)
{
	InstancingPolicy = EGameplayAbilityInstancingPolicy::InstancedPerActor;
}
