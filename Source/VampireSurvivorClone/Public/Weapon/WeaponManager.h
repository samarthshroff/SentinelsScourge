// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayAbilitySpecHandle.h"
#include "GameplayTagContainer.h"
#include "UObject/Object.h"
#include "WeaponManager.generated.h"

struct FWeaponMetaData;
class UWeaponData;
class UWeaponAttributeSet;

USTRUCT()
struct FWeaponInfo
{
	GENERATED_BODY()

	UPROPERTY()
	FGameplayTag Category;

	UPROPERTY()
	FGameplayTag Name;

	UPROPERTY()
	FGameplayAbilitySpecHandle SpecHandle;

	UPROPERTY()
	TObjectPtr<UWeaponAttributeSet> AttributeSet;

	FWeaponInfo() = default;

	FWeaponInfo(const FWeaponInfo& Other) = default;
	FWeaponInfo& operator=(const FWeaponInfo& Other) = default;	
	FWeaponInfo(FWeaponInfo&& Other) noexcept = default;	
	FWeaponInfo& operator=(FWeaponInfo&& Other) noexcept = default;
};

/**
 * 
 */
UCLASS()
class VAMPIRESURVIVORCLONE_API UWeaponManager : public UObject
{
	GENERATED_BODY()

	UPROPERTY()
	TObjectPtr<UWeaponData> WeaponDataAsset;

	// TODO - remove the entry if the associated ability is removed from the ability system.
	UPROPERTY()
	TMap<FGameplayTag, FWeaponInfo> AcquiredWeapons;
	
public:
	void Initialize(const TObjectPtr<UWeaponData>& InWeaponData);
	
	TOptional<const FWeaponInfo> GetCachedWeapon(const FGameplayTag& WeaponTag);
	TOptional<const FWeaponMetaData> GetWeaponFromDataAsset(const FGameplayTag& WeaponTag);
	TOptional<const FGameplayTag> GetGameplayTagFromSpecHandle(const FGameplayAbilitySpecHandle& Handle) const;	
	const UWeaponAttributeSet* GetWeaponAttributeSetForSpecHandle(const FGameplayAbilitySpecHandle& Handle) const;	
	
	void SetWeaponSpecHandleAndAttributeSet(const FGameplayTag& WeaponTag, FGameplayAbilitySpecHandle& Handle, TObjectPtr<UWeaponAttributeSet> 
	AttributeSet);
	
};
