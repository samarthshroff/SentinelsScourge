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
	
	TOptional<FWeaponInfo> GetCachedWeapon(const FGameplayTag& WeaponTag);
	TOptional<FWeaponMetaData> GetWeaponFromDataAsset(const FGameplayTag& WeaponTag);
	
	void SetWeaponSpecHandleAndAttributeSet(const FGameplayTag& WeaponTag, const FGameplayAbilitySpecHandle& Handle,
	const TObjectPtr<UWeaponAttributeSet>& AttributeSet);
	
};
