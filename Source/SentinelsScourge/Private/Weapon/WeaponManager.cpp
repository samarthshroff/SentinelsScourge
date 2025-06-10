// Copyright (c) Samarth Shroff. All Rights Reserved.
// This work is protected under applicable copyright laws in perpetuity.
// Licensed under the CC BY-NC-ND 4.0 License. See LICENSE file for details.

#include "Weapon/WeaponManager.h"

#include "Weapon/WeaponData.h"

void UWeaponManager::Initialize(const TObjectPtr<UWeaponData>& InWeaponData)
{
	WeaponDataAsset = InWeaponData;
	AcquiredWeapons.Reset();
}

TOptional<const FWeaponInfo> UWeaponManager::GetCachedWeapon(const FGameplayTag& WeaponTag)
{	
	if (AcquiredWeapons.IsEmpty()) return NullOpt;

	if (FWeaponInfo* WeaponInfo = AcquiredWeapons.Find(WeaponTag))
	{
		return *WeaponInfo;
	}

	return NullOpt;
}

TOptional<const FWeaponMetaData> UWeaponManager::GetWeaponFromDataAsset(const FGameplayTag& WeaponTag)
{
	if (!WeaponDataAsset) return NullOpt;

	TOptional<const FWeaponMetaData> WeaponMetaData = WeaponDataAsset->FindAbilityDataForTag(WeaponTag, true);
	
	if (WeaponMetaData.IsSet())
	{		
		FWeaponInfo WeaponInfo = AcquiredWeapons.FindOrAdd(WeaponTag);
		WeaponInfo.Category = WeaponMetaData.GetValue().Category;
		WeaponInfo.Name = WeaponMetaData.GetValue().Name;
		AcquiredWeapons.Add(WeaponTag, WeaponInfo);
	}
	
	return WeaponMetaData;	
}

TOptional<const FGameplayTag> UWeaponManager::GetGameplayTagFromSpecHandle(const FGameplayAbilitySpecHandle& Handle) const
{
	check(Handle.IsValid());

	if (AcquiredWeapons.IsEmpty()) return NullOpt;

	for (TTuple<FGameplayTag, FWeaponInfo> Weapon : AcquiredWeapons)
	{
		if (Weapon.Value.SpecHandle != Handle)
		{
			continue;
		}
		return Weapon.Key;
	}
	return NullOpt;
}

const UWeaponAttributeSet* UWeaponManager::GetWeaponAttributeSetForSpecHandle(const FGameplayAbilitySpecHandle& Handle) const
{
	check(Handle.IsValid());

	if (AcquiredWeapons.IsEmpty()) return nullptr;

	for (TTuple<FGameplayTag, FWeaponInfo> Weapon : AcquiredWeapons)
	{
		if (Weapon.Value.SpecHandle != Handle)
		{
			continue;
		}
		return Weapon.Value.AttributeSet;
	}
	return nullptr;
}

void UWeaponManager::SetWeaponSpecHandleAndAttributeSet(const FGameplayTag& WeaponTag, FGameplayAbilitySpecHandle& Handle, TObjectPtr<UWeaponAttributeSet> 
AttributeSet)
{
	if (AcquiredWeapons.IsEmpty()) return;

	if (FWeaponInfo* WeaponInfo = AcquiredWeapons.Find(WeaponTag))
	{
		WeaponInfo->SpecHandle = Handle;
		WeaponInfo->AttributeSet = AttributeSet;
	}
}
