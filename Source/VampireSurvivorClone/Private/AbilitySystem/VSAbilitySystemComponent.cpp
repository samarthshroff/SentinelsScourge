// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/VSAbilitySystemComponent.h"

#include "VampireSurvivorGameplayTags.h"
#include "Weapon/WeaponData.h"
#include "Weapon/WeaponManager.h"
#include "AbilitySystem/WeaponAttributeSet.h"
#include "AbilitySystem/Abilities/VSGameplayAbility.h"
#include "AbilitySystem/Abilities/VSGameplayAbilityInterface.h"
#include "AbilitySystem/Generated/WeaponAttributeSets/MagicWandAttributeSet.h"
#include "Player/PlayerCharacterState.h"

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
			TOptional<const FWeaponInfo> ExistingWeaponInfo = WeaponManager->GetCachedWeapon(AbilityTag);

			if (ExistingWeaponInfo.IsSet())
			{
				int WeaponLevel = ExistingWeaponInfo.GetValue().AttributeSet->GetLevel();
				++WeaponLevel;
				ExistingWeaponInfo.GetValue().AttributeSet->SetLevel(WeaponLevel);
			}
			else
			{
				TOptional<const FWeaponMetaData> WeaponMetaData = WeaponManager->GetWeaponFromDataAsset(AbilityTag);
				if (!WeaponMetaData.IsSet())
				{
					UE_LOG(LogTemp, Error, TEXT("Could not acquire ability %s"), *AbilityTag.ToString());
					return;
				}

				const TSubclassOf<UWeaponAttributeSet> AttributeSetClass = WeaponMetaData.GetValue().AttributeSet.LoadSynchronous();
				const UWeaponAttributeSet* AttributeSetConst = Cast<UWeaponAttributeSet>(GetOrCreateAttributeSubobject(AttributeSetClass));
				UWeaponAttributeSet* AttributeSet = const_cast<UWeaponAttributeSet*>(AttributeSetConst);
				// UWeaponAttributeSet* AttributeSet = NewObject<UWeaponAttributeSet>(GetOwner(), AttributeSetClass);
				// //AddAttributeSetSubobject(AttributeSet);
				// //ForceReplication();
				// AddSpawnedAttribute(AttributeSet);

				InitStats(AttributeSetClass, nullptr);

				// Add Gameplay Ability
				const TSubclassOf<UGameplayAbility> AbilityClass = WeaponMetaData.GetValue().AbilityClass.LoadSynchronous();
				const FGameplayAbilitySpec Spec (AbilityClass,1);
				FGameplayAbilitySpecHandle AbilitySpecHandle = GiveAbility(Spec);
				
				// Store for later use
				WeaponManager->SetWeaponSpecHandleAndAttributeSet(AbilityTag, AbilitySpecHandle, AttributeSet);

				// Apply default gameplay effect here
				const TSubclassOf<UGameplayEffect> DefaultAttributeEffect = WeaponMetaData.GetValue().DefaultAttributes.LoadSynchronous();
				FGameplayEffectContextHandle ContextHandle = MakeEffectContext();
				ContextHandle.AddSourceObject(GetAvatarActor());
				
				// default level to 1.0 as there is a gameplay effect based on weapon level that is applied from the default gameplay effect (directly or indirectly). 
				// TODO - For now only defaults and influenced are applied. Not all MMCs for influenced ready. Also not applied the level up attribute from influenced.
				FGameplayEffectSpecHandle SpecHandle = MakeOutgoingSpec(DefaultAttributeEffect, 1.0f,ContextHandle);
				ApplyGameplayEffectSpecToSelf(*SpecHandle.Data.Get());
				
				Cast<IVSGameplayAbilityInterface>(FindAbilitySpecFromHandle(AbilitySpecHandle)->GetPrimaryInstance())->Initialize(AttributeSet->GetCooldown(), this);
				
				// TODO - activate will not be here. kept for testing. it will go somewhere else - maybe once level 
				//  is ready event
				TryActivateAbility(AbilitySpecHandle);				
			}
		}
}



void UVSAbilitySystemComponent::Initialize(const TObjectPtr<UWeaponData>& WeaponData)
{
	if (WeaponManager == nullptr)
	{
		WeaponManager = NewObject<UWeaponManager>(this);
	}
	WeaponManager->Initialize(WeaponData);
	
	//OnAnyGameplayEffectRemovedDelegate().AddUObject(this, &UVSAbilitySystemComponent::OnAnyGameplayEffectRemoved);
	UVSGameplayAbility::OnAbilityCooldownCompleteDelegate.AddUObject(this, &UVSAbilitySystemComponent::OnAbilityCooldownComplete);
}

UWeaponManager* UVSAbilitySystemComponent::GetWeaponManager()
{
	return WeaponManager;
}

FActiveGameplayEffectHandle UVSAbilitySystemComponent::ApplyGameplayEffectSpecToSelf(const FGameplayEffectSpec& GameplayEffect, FPredictionKey PredictionKey)
{
	//UE_LOG(LogTemp, Display, TEXT("UVSAbilitySystemComponent::ApplyGameplayEffectSpecToSelf"));
	return Super::ApplyGameplayEffectSpecToSelf(GameplayEffect, PredictionKey);
}

void UVSAbilitySystemComponent::OnAbilityCooldownComplete(const FActiveGameplayEffect* ActiveGameplayEffect)
{
	const TObjectPtr<const UGameplayEffect> GameplayEffect = ActiveGameplayEffect->Spec.Def;
	
	if (GameplayEffect->DurationPolicy == EGameplayEffectDurationType::HasDuration)
	{
		TArray<FGameplayTag> AssetTags = GameplayEffect->GetAssetTags().GetGameplayTagArray();

		// Check if this is a cooldown GE
		bool bIsCooldownGE = false;
		for (FGameplayTag Tag : AssetTags)
		{
			if (Tag.MatchesTag(VampireSurvivorGameplayTags::Weapon_Cooldown))
			{
				bIsCooldownGE = true;
				break;
			}
		}

		// not using inverted condition and returning in case i have to use this function for other effects.
		if (bIsCooldownGE)
		{
			// Get the ability spec and activate it 
			for (FGameplayTag Tag : AssetTags)
			{
				TOptional<const FWeaponInfo> Weapon = WeaponManager->GetCachedWeapon(Tag);
				if (Weapon.IsSet())
				{
					if (Weapon->Name.MatchesTagExact(VampireSurvivorGameplayTags::Weapon_Hero_MagicWand))
					{
						return;
					}
					TryActivateAbility(Weapon.GetValue().SpecHandle);
				}
			}
		}
	}	
}

// void UVSAbilitySystemComponent::OnAnyGameplayEffectRemoved(const FActiveGameplayEffect& ActiveGameplayEffect)
// {
// 	const TObjectPtr<const UGameplayEffect> GameplayEffect = ActiveGameplayEffect.Spec.Def;
// 	
// 	if (GameplayEffect->DurationPolicy == EGameplayEffectDurationType::HasDuration)
// 	{
// 		TArray<FGameplayTag> AssetTags = GameplayEffect->GetAssetTags().GetGameplayTagArray();
//
// 		// Check if this is a cooldown GE
// 		bool bIsCooldownGE = false;
// 		for (FGameplayTag Tag : AssetTags)
// 		{
// 			if (Tag.MatchesTag(VampireSurvivorGameplayTags::Weapon_Cooldown))
// 			{
// 				bIsCooldownGE = true;
// 				break;
// 			}
// 		}
//
// 		// not using inverted condition and returning in case i have to use this function for other effects.
// 		if (bIsCooldownGE)
// 		{
// 			// Get the ability spec and activate it 
// 			for (FGameplayTag Tag : AssetTags)
// 			{
// 				TOptional<const FWeaponInfo> Weapon = WeaponManager->GetCachedWeapon(Tag);
// 				if (Weapon.IsSet())
// 				{
// 					TryActivateAbility(Weapon.GetValue().SpecHandle);
// 				}
// 			}
// 		}
// 	}	
// }

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
