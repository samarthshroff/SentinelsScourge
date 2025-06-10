// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/ModMagCalc/WeaponMMC_Helper.h"

#include "AbilitySystemInterface.h"
#include "AbilitySystem/PlayerAttributeSet.h"
#include "AbilitySystem/HeroAbilitySystemComponent.h"
#include "Weapon/WeaponManager.h"

UHeroAbilitySystemComponent* UWeaponMMC_Helper::AbilitySystemComponent = nullptr;
const UPlayerAttributeSet* UWeaponMMC_Helper::PlayerAttributeSet = nullptr;

void UWeaponMMC_Helper::InitializeAbilitySystemComponent(const FGameplayEffectSpec& Spec)
{
	if (AbilitySystemComponent == nullptr)
	{
		IAbilitySystemInterface* ASI = Cast<IAbilitySystemInterface>(Spec.GetContext().GetSourceObject());
		AbilitySystemComponent = Cast<UHeroAbilitySystemComponent>(ASI->GetAbilitySystemComponent());
	}
}

const UWeaponAttributeSet* UWeaponMMC_Helper::GetWeaponAttributeSet(const FGameplayEffectSpec& Spec)
{
	InitializeAbilitySystemComponent(Spec);
	// get the current valur of the attribute this MMC is affecting
	FGameplayTagContainer AllAssetTags;
	Spec.GetAllAssetTags(AllAssetTags);
	const FGameplayTag WeaponTag = AllAssetTags.First();

	// by this time the weapon will be and must be part of the weapon manager, as GiveAbility is and must always
	// be called before applying the gameplay effects (as Attribute set is also set with GiveAbility).
	return AbilitySystemComponent->GetWeaponManager()->GetCachedWeapon(WeaponTag)->AttributeSet;
}

const UPlayerAttributeSet* UWeaponMMC_Helper::GetPlayerAttributeSet(const FGameplayEffectSpec& Spec)
{
	if (PlayerAttributeSet == nullptr)
	{
		InitializeAbilitySystemComponent(Spec);
		PlayerAttributeSet = Cast<UPlayerAttributeSet>(AbilitySystemComponent->GetAttributeSet(UPlayerAttributeSet::StaticClass()));
	}
	return PlayerAttributeSet;
}
