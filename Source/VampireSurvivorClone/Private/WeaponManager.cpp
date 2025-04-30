// Fill out your copyright notice in the Description page of Project Settings.


#include "WeaponManager.h"

#include "WeaponData.h"

void UWeaponManager::Initialize(const TObjectPtr<UWeaponData>& InWeaponData)
{
	WeaponDataAsset = InWeaponData;
	AcquiredWeapons.Reset();
}

FWeaponInfo* UWeaponManager::GetCachedWeapon(const FGameplayTag& WeaponTag)
{	
	if (AcquiredWeapons.IsEmpty()) return nullptr;

	if (FWeaponInfo* WeaponInfo = AcquiredWeapons.Find(WeaponTag))
	{
		return WeaponInfo;
	}

	return nullptr;
}

FWeaponMetaData* UWeaponManager::GetWeaponFromDataAsset(const FGameplayTag& WeaponTag)
{
	if (!WeaponDataAsset) return nullptr;

	FWeaponMetaData* WeaponMetaData = WeaponDataAsset->FindAbilityDataForTag(WeaponTag, true);
	if (WeaponMetaData != nullptr)
	{
		FWeaponInfo WeaponInfo = AcquiredWeapons.FindOrAdd(WeaponTag);
		WeaponInfo.Category = WeaponMetaData->Category;
		WeaponInfo.Name = WeaponMetaData->Name;
	}
	
	return WeaponMetaData;	
}

void UWeaponManager::SetWeaponSpecHandleAndAttributeSet(const FGameplayTag& WeaponTag, const FGameplayAbilitySpecHandle& Handle, const TObjectPtr<UWeaponAttributeSet>& AttributeSet)
{
	if (AcquiredWeapons.IsEmpty()) return;

	if (FWeaponInfo* WeaponInfo = AcquiredWeapons.Find(WeaponTag))
	{
		WeaponInfo->SpecHandle = Handle;
		WeaponInfo->AttributeSet = AttributeSet;
	}
}
