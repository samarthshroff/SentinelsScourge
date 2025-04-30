// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/VSAbilitySystemComponent.h"

#include "WeaponData.h"
#include "WeaponManager.h"
#include "AbilitySystem/WeaponAttributeSet.h"
#include "AbilitySystem/Abilities/VSGameplayAbility.h"
#include "AbilitySystem/Generated/WeaponAttributeSets/MagicWandAttributeSet.h"

UVSAbilitySystemComponent::UVSAbilitySystemComponent(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	ReplicationMode = EGameplayEffectReplicationMode::Full;
}

void UVSAbilitySystemComponent::AcquireAbility(const FGameplayTag& AbilityTag)
{
		// // Check if the tag is present in the possessed weapons array
		// // if so then get the ability handle spec and increment the level attribute of this weapon by 1
		// // ELSE
		// // Get the weapon row from the data table
		// // create an instance of a weapon ability based on the weapon category tag
		// // Add either niagara system component or static mesh depending on the value of the niagara system soft class ptr is null or not.
		//
		bool bIsWeapon = AbilityTag.ToString().Contains("Weapon");
		
		if (bIsWeapon && WeaponManager != nullptr)
		{
			const TOptional<FWeaponInfo> ExistingWeaponInfo = WeaponManager->GetCachedWeapon(AbilityTag);

			if (ExistingWeaponInfo.IsSet())
			{
				int WeaponLevel = ExistingWeaponInfo->AttributeSet->GetLevel();
				++WeaponLevel;
				ExistingWeaponInfo->AttributeSet->SetLevel(WeaponLevel);
			}
			else
			{
				const TOptional<FWeaponMetaData> WeaponMetaData = WeaponManager->GetWeaponFromDataAsset(AbilityTag);
				if (!WeaponMetaData.IsSet())
				{
					UE_LOG(LogTemp, Error, TEXT("Could not acquire ability %s"), *AbilityTag.ToString());
					return;
				}

				const TSubclassOf<UGameplayAbility> AbilityClass = WeaponMetaData->AbilityClass.LoadSynchronous();
				const FGameplayAbilitySpec Spec (AbilityClass,1);
				const FGameplayAbilitySpecHandle Handle = GiveAbility(Spec);

				const TSubclassOf<UWeaponAttributeSet> AttributeSetClass = WeaponMetaData->AttributeSet.LoadSynchronous();
				UWeaponAttributeSet* AttributeSet = NewObject<UWeaponAttributeSet>(this, AttributeSetClass);
				AddSpawnedAttribute(AttributeSet);

				WeaponManager->SetWeaponSpecHandleAndAttributeSet(AbilityTag, Handle, AttributeSet);

				TryActivateAbility(Handle);
			}
		}
}

void UVSAbilitySystemComponent::InitWeaponManager(const TObjectPtr<UWeaponData>& WeaponData)
{
	if (WeaponManager == nullptr)
	{
		WeaponManager = NewObject<UWeaponManager>(this);		
	}
	WeaponManager->Initialize(WeaponData);
}

// bool UVSAbilitySystemComponent::PossessAbility(FGameplayTag AbilityTag)
// {
// 	// Check if the tag is present in the possessed weapons array
// 	// if so then get the ability handle spec and increment the level attribute of this weapon by 1
// 	// ELSE
// 	// Get the weapon row from the data table
// 	// create an instance of a weapon ability based on the weapon category tag
// 	// Add either niagara system component or static mesh depending on the value of the niagara system soft class ptr is null or not.
//
// 	if (PossessedAbilities.Contains(AbilityTag))
// 	{
// 		FGameplayAbilitySpecHandle SpecHandle = PossessedAbilities[AbilityTag];
//
// 		//GetSet<UWeaponAttributSet>()		
// 	}
//
// 	
// 	return false;
// }


// void UVSAbilitySystemComponent::AddCharacterAbilities(const TArray<TSubclassOf<UGameplayAbility>>& StartupAbilities)
// {
// 	for (const TSubclassOf<UGameplayAbility> AbilityClass : StartupAbilities)
// 	{
// 		FGameplayAbilitySpec AbilitySpec (AbilityClass, 1);
// 		if (const UVSGameplayAbility* Ability = Cast<UVSGameplayAbility>(AbilitySpec.Ability))
// 		{
// 			GiveAbility(AbilitySpec);
// 		}		
// 	}	
// }

// void UVSAbilitySystemComponent::ActivateAcquiredAbilities()
// {
// 	for (FGameplayAbilitySpecHandle Handle : AcquiredAbilities)
// 	{
// 		TryActivateAbility(Handle);
// 	}
// }
