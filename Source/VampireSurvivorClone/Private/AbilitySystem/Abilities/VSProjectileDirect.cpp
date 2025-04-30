// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/Abilities/VSProjectileDirect.h"

UVSProjectileDirect::UVSProjectileDirect()
{
	
}

void UVSProjectileDirect::ActivateAbility(const FGameplayAbilitySpecHandle Handle,
	const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
	const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

	// Spawn the projectile here.
}
