// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/Abilities/MagicWandAbility.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "VampireSurvivorGameplayTags.h"
#include "AbilitySystem/VSAbilitySystemComponent.h"
#include "AbilitySystem/WeaponAttributeSet.h"
#include "AbilitySystem/AbilityTasks/AbilityTask_HomingProjectile.h"
#include "Character/CharacterBaseInterface.h"
#include "VampireSurvivorClone/VampireSurvivorClone.h"
#include "Weapon/WeaponManager.h"

UMagicWandAbility::UMagicWandAbility()
{
}

UMagicWandAbility::~UMagicWandAbility()
{
	// CooldownEffectSpec = nullptr;
	// delete CooldownEffectSpec;
}

void UMagicWandAbility::OnCooldownComplete(const FGameplayEffectRemovalInfo& GameplayEffectRemovalInfo) const
{		
	if (HomingProjectileTask != nullptr)
	{
		UE_LOG(LogTemp, Log, TEXT("UMagicWandAbility::OnCooldownComplete call HomingProjectileTask->SpawnProjectile()"));
		HomingProjectileTask->SpawnProjectile();

		if (Cooldown.IsSet())
		{
			// Commit Cooldown is a non-const so calling it from an event listener
			bool bIsExecute = OnThisAbilityCooldownCompleted.ExecuteIfBound();
		}	
	}
}

void UMagicWandAbility::ApplyCooldown(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
	const FGameplayAbilityActivationInfo ActivationInfo) const
{	
	if (CooldownGameplayEffectClass != nullptr)
	{
		// Make a spec handle from existing (applied) cooldown gameplay effect tsubclass 
		FGameplayEffectSpecHandle SpecHandle = MakeOutgoingGameplayEffectSpec(CooldownGameplayEffectClass, 1.0f);

		// Seems like the SetSetByCallerMagnitude is not updating the duration value. So calling SetDuration manually.
		SpecHandle.Data.Get()->SetSetByCallerMagnitude(VampireSurvivorGameplayTags::Weapon_Cooldown, Cooldown.GetValue());
		SpecHandle.Data.Get()->SetDuration(Cooldown.GetValue(), false);

		// ApplyGameplayEffectSpecToOwner is buggy for me. Was not returning a valid value so using the source function directly.
		FActiveGameplayEffectHandle CooldownActiveHandle = GetAbilitySystemComponentFromActorInfo()->ApplyGameplayEffectSpecToSelf(*SpecHandle.Data.Get());
				
		if (UVSAbilitySystemComponent* ASC = Cast<UVSAbilitySystemComponent>(GetAbilitySystemComponentFromActorInfo()))
		{
			if (!CooldownActiveHandle.IsValid())
			{
				UE_LOG(LogTemp, Error, TEXT("Cooldown handle is invalid — effect probably wasn't applied."));
				return;
			}
			
			FDelegateHandle DelegateHandle;
			FOnActiveGameplayEffectRemoved_Info* RemovalDelegate = ASC->OnGameplayEffectRemoved_InfoDelegate(CooldownActiveHandle);

			if (RemovalDelegate)
			{
				DelegateHandle = RemovalDelegate->AddUObject(this, &UMagicWandAbility::OnCooldownComplete);
			}
			else
			{
				UE_LOG(LogTemp, Warning, TEXT("Failed to bind cooldown complete delegate: RemovalDelegate is null"));
			}
		}
	}
	else
	{
		UE_LOG(LogTemp, Log, TEXT("UMagicWandAbility::ApplyCooldown CooldownGameplayEffectClass is null"));
	}
}

void UMagicWandAbility::ActivateAbility(const FGameplayAbilitySpecHandle Handle,
                                        const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
                                        const FGameplayEventData* TriggerEventData)
{
	//Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);
	// have a for loop of how many projectiles to spawn (Amount)
	// in the for loop have a timer that checks against the projectile interval and spawns a projectile.
	// first projectile does not consider this above timer.
	// spawn the projectile deferred
	// send the move speed and maybe pierce and block by walls in the initialize function
	// finish spawning

	// the whole above logic will go in the ability task

	OnThisAbilityCooldownCompleted.BindLambda([&]()
	{
		UE_LOG(LogTemp, Log, TEXT("UMagicWandAbility::OnThisAbilityCooldownCompleted Lambda Committing Cooldown"));
		// Commit Cooldown is a non-const so calling it from an event listener executed from OnCooldownComplete which is a const. 
		CommitAbilityCooldown(CurrentSpecHandle,CurrentActorInfo,CurrentActivationInfo,true);
	});
	
	if (const ICharacterBaseInterface* Actor = Cast<ICharacterBaseInterface>(GetAvatarActorFromActorInfo()))
	{
		if (UVSAbilitySystemComponent* ASC = Cast<UVSAbilitySystemComponent>(GetAbilitySystemComponentFromActorInfo()))
		{
			UWeaponManager* WeaponManager = ASC->GetWeaponManager();
			const FGameplayTag Tag = WeaponManager->GetGameplayTagFromSpecHandle(Handle).GetValue();
			// TODO - may pass (FWeaponInfo) struct instead of passing the whole weaponmanager. pass by reference.
			HomingProjectileTask = UAbilityTask_HomingProjectile::CreateHomingProjectile(this, Tag.GetTagName(), Tag, 
			HomingProjectileClass, WeaponManager);
			HomingProjectileTask->SpawnProjectile();

			if (Cooldown.IsSet())
			{
				UE_LOG(LogTemp, Log, TEXT("Committing Cooldown"));
				CommitAbilityCooldown(Handle,ActorInfo,ActivationInfo,true);
			}	
		}
	}	
}

void UMagicWandAbility::Initialize(const float InCooldown, UAbilitySystemComponent* InAbilitySystemComponent)
{
	// // I can pass the ASC object as param to Initialize too. but that would mean that the interface has to know UVSAbilitySystemComponent
	// // An Interface having a dependency on another class is not a good design.
	// if (const UVSAbilitySystemComponent* ASC = Cast<UVSAbilitySystemComponent>(InAbilitySystemComponent))
	// {
		if (!Cooldown.IsSet())
		{	
			Cooldown = InCooldown;
			UE_LOG(LogTemp, Log, TEXT("UMagicWandAbility::Initialize The Magic Wand Cooldown is %f"), Cooldown.GetValue());
		}
		
		// if (const UGameplayEffect* CooldownEffect = GetCooldownGameplayEffect())
		// {
		// 	CooldownGESpecHandle = MakeOutgoingGameplayEffectSpec(CooldownEffect->GetClass(), 1.0f);
		// }
		
	// 	if (CooldownEffectSpec == nullptr)
	// 	{
	// 		UGameplayEffect* CooldownEffect = GetCooldownGameplayEffect();
	// 		FGameplayEffectContextHandle ContextHandle = ASC->MakeEffectContext();
	// 		ContextHandle.AddSourceObject(ASC->GetAvatarActor());
	// 		CooldownGESpecHandle = UAbilitySystemBlueprintLibrary::MakeSpecHandle(CooldownEffect, GetOwningActorFromActorInfo(), GetAvatarActorFromActorInfo(), 1.0f)
	// 		// Set the cooldown value
	// 		CooldownEffectSpec = new FGameplayEffectSpec(CooldownEffect, ContextHandle, 1.0f);
	// 	}
	// }
}
