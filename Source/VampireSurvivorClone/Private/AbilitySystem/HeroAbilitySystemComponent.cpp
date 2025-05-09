// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/HeroAbilitySystemComponent.h"

#include "VampireSurvivorGameplayTags.h"
#include "Weapon/WeaponData.h"
#include "Weapon/WeaponManager.h"
#include "AbilitySystem/WeaponAttributeSet.h"
#include "AbilitySystem/Abilities/VSGameplayAbility.h"
#include "AbilitySystem/Abilities/VSGameplayAbilityInterface.h"

UHeroAbilitySystemComponent::UHeroAbilitySystemComponent(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	ReplicationMode = EGameplayEffectReplicationMode::Full;
}

void UHeroAbilitySystemComponent::AcquireAbility(const FGameplayTag& AbilityTag)
{
		// // Check if the tag is present in the possessed weapons array
		// // if so then get the ability handle spec and increment the level attribute of this weapon by 1
		// // ELSE
		// // Get the weapon row from the data table
		// // create an instance of a weapon ability based on the weapon category tag
		// // Add either niagara system component or static mesh depending on the value of the niagara system soft class ptr is null or not.
		//
		const bool bIsWeapon = AbilityTag.ToString().Contains("Weapon");

		// If ability is a weapon
		if (bIsWeapon && WeaponManager != nullptr)
		{
			// Check if it is already in use
			TOptional<const FWeaponInfo> ExistingWeaponInfo = WeaponManager->GetCachedWeapon(AbilityTag);

			// If in use (given) then update the weapon level.
			if (ExistingWeaponInfo.IsSet())
			{
				int WeaponLevel = ExistingWeaponInfo.GetValue().AttributeSet->GetLevel();
				++WeaponLevel;
				ExistingWeaponInfo.GetValue().AttributeSet->SetLevel(WeaponLevel);
			}
			else // Else create a new weapon (ability) and give it to the Owning Actor.
			{
				TOptional<const FWeaponMetaData> WeaponMetaDataOptional = WeaponManager->GetWeaponFromDataAsset(AbilityTag);
				if (!WeaponMetaDataOptional.IsSet())
				{
					UE_LOG(LogTemp, Error, TEXT("Could not acquire ability %s"), *AbilityTag.ToString());
					return;
				}
				const FWeaponMetaData WeaponMetaData = WeaponMetaDataOptional.GetValue();
				
				// Add Associated weapon attribute set
				const TSubclassOf<UWeaponAttributeSet> AttributeSetClass = WeaponMetaData.AttributeSet.LoadSynchronous();
				const UWeaponAttributeSet* AttributeSetConst = Cast<UWeaponAttributeSet>(GetOrCreateAttributeSubobject(AttributeSetClass));
				UWeaponAttributeSet* AttributeSet = const_cast<UWeaponAttributeSet*>(AttributeSetConst);
				InitStats(AttributeSetClass, nullptr);

				// Add Gameplay Ability
				const TSubclassOf<UGameplayAbility> AbilityClass = WeaponMetaData.AbilityClass.LoadSynchronous();
				const FGameplayAbilitySpec Spec (AbilityClass,1);
				FGameplayAbilitySpecHandle AbilitySpecHandle = GiveAbility(Spec);
				
				// Store for later use
				WeaponManager->SetWeaponSpecHandleAndAttributeSet(AbilityTag, AbilitySpecHandle, AttributeSet);

				// Apply default gameplay effect here
				const TSubclassOf<UGameplayEffect> DefaultAttributeEffect = WeaponMetaData.DefaultAttributes.LoadSynchronous();
				FGameplayEffectContextHandle ContextHandle = MakeEffectContext();
				ContextHandle.AddSourceObject(GetAvatarActor());
				
				// default level to 1.0 as there is a gameplay effect based on weapon level that is applied from the default gameplay effect (directly or indirectly). 
				// TODO - For now only defaults and influenced are applied. Not all MMCs for influenced ready. Also not applied the level up attribute from influenced.
				FGameplayEffectSpecHandle SpecHandle = MakeOutgoingSpec(DefaultAttributeEffect, 1.0f,ContextHandle);
				ApplyGameplayEffectSpecToSelf(*SpecHandle.Data.Get());

				Cast<IVSGameplayAbilityInterface>(FindAbilitySpecFromHandle(AbilitySpecHandle)->GetPrimaryInstance())->Initialize(AttributeSet->GetCooldown());
				
				// TODO - activate MAY not be here. kept for testing. it will go somewhere else - maybe once level 
				//  is ready event
				TryActivateAbility(AbilitySpecHandle);
			}
		}
}

void UHeroAbilitySystemComponent::Initialize(const TObjectPtr<UWeaponData>& WeaponData)
{
	if (WeaponManager == nullptr)
	{
		WeaponManager = NewObject<UWeaponManager>(this);
	}
	WeaponManager->Initialize(WeaponData);
	
	UVSGameplayAbility::OnAbilityCooldownCompleteDelegate.AddUObject(this, &UHeroAbilitySystemComponent::OnAbilityCooldownComplete);
}

UWeaponManager* UHeroAbilitySystemComponent::GetWeaponManager()
{
	return WeaponManager;
}

FActiveGameplayEffectHandle UHeroAbilitySystemComponent::ApplyGameplayEffectSpecToSelf(const FGameplayEffectSpec& GameplayEffect, FPredictionKey PredictionKey)
{
	return Super::ApplyGameplayEffectSpecToSelf(GameplayEffect, PredictionKey);
}

void UHeroAbilitySystemComponent::OnAbilityCooldownComplete(const FActiveGameplayEffect* ActiveGameplayEffect)
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
					// Ignore cooldown from Magic wand as the cooldown is captured in the ability itself.
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
