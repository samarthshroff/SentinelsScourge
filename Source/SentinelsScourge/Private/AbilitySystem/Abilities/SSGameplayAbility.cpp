// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/Abilities/SSGameplayAbility.h"


FOnAbilityCooldownComplete USSGameplayAbility::OnAbilityCooldownCompleteDelegate;

void USSGameplayAbility::Initialize(float InCooldown)
{
	InstancingPolicy = EGameplayAbilityInstancingPolicy::InstancedPerActor;
}
