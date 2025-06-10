// Copyright (c) Samarth Shroff. All Rights Reserved.
// This work is protected under applicable copyright laws in perpetuity.
// Licensed under the CC BY-NC-ND 4.0 License. See LICENSE file for details.

#include "AbilitySystem/ModMagCalc/MMC_WeaponDamage.h"

#include "AbilitySystemInterface.h"
#include "AbilitySystem/PlayerAttributeSet.h"
#include "AbilitySystem/HeroAbilitySystemComponent.h"
#include "Weapon/WeaponManager.h"
#include "AbilitySystem/WeaponAttributeSet.h"
#include "AbilitySystem/ModMagCalc/WeaponMMC_Helper.h"


UMMC_WeaponDamage::UMMC_WeaponDamage()
{
}

float UMMC_WeaponDamage::CalculateBaseMagnitude_Implementation(const FGameplayEffectSpec& Spec) const
{
	//return Super::CalculateBaseMagnitude_Implementation(Spec);
	float Damage = 0.0f;

	const UWeaponAttributeSet* WeaponAttributeSet = UWeaponMMC_Helper::GetWeaponAttributeSet(Spec);
	if (WeaponAttributeSet != nullptr)
	{
		Damage = WeaponAttributeSet->GetDamage();	
	}
	
	const UPlayerAttributeSet* PlayerAttributeSet = UWeaponMMC_Helper::GetPlayerAttributeSet(Spec);
	if (PlayerAttributeSet != nullptr)
	{
		// 110/100 = 1.1
		const float PlayerMight = PlayerAttributeSet->GetMight();
		Damage = Damage * PlayerMight;
	}
	return Damage;
}
