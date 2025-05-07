// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/ModMagCalc/MMC_WeaponDamage.h"

#include "AbilitySystemInterface.h"
#include "AbilitySystem/PlayerAttributeSet.h"
#include "AbilitySystem/VSAbilitySystemComponent.h"
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
		const float PlayerMight = (PlayerAttributeSet->GetMight() - 100.0f)/100.0f;
		Damage = Damage + (Damage * PlayerMight);
	}
	return Damage;
}
