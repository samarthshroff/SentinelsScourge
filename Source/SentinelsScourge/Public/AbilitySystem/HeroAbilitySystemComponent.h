// Copyright (c) Samarth Shroff. All Rights Reserved.
// This work is protected under applicable copyright laws in perpetuity.
// Licensed under the CC BY-NC-ND 4.0 License. See LICENSE file for details.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "HeroAbilitySystemComponent.generated.h"

class UWeaponManager;
class UWeaponData;
struct FSSAbilityData;
/**
 * Project's Main Ability System Component.
 */
UCLASS()
class SENTINELSSCOURGE_API UHeroAbilitySystemComponent : public UAbilitySystemComponent
{
	GENERATED_BODY()

private:
	UPROPERTY()
	TObjectPtr<UWeaponManager> WeaponManager = nullptr;

public:
	UHeroAbilitySystemComponent(const FObjectInitializer &ObjectInitializer);
	void AcquireAbility(const FGameplayTag &AbilityTag);

	void Initialize(const TObjectPtr<UWeaponData> &WeaponData);
	UWeaponManager *GetWeaponManager();

	virtual FActiveGameplayEffectHandle ApplyGameplayEffectSpecToSelf(const FGameplayEffectSpec &GameplayEffect,
																	  FPredictionKey PredictionKey = FPredictionKey()) override;

private:
	// USSGameplayAbility::OnAbilityCooldownCompleteDelegate's function delegate.
	void OnAbilityCooldownComplete(const FActiveGameplayEffect *ActiveGameplayEffect);
};
