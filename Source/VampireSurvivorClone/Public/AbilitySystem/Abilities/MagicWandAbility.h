// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "VSGameplayAbility.h"
#include "VSGameplayAbilityInterface.h"
#include "MagicWandAbility.generated.h"

class UAbilityTask_HomingProjectile;
class AProjectileHoming;

DECLARE_DELEGATE(FOnThisAbilityCooldownCompletedDelegate);

/**
 * 
 */
UCLASS()
class VAMPIRESURVIVORCLONE_API UMagicWandAbility : public UVSGameplayAbility
{
	GENERATED_BODY()

private:
	UPROPERTY()
	TObjectPtr<UAbilityTask_HomingProjectile> HomingProjectileTask;

	TOptional<float> Cooldown;
	//
	// FGameplayEffectSpec* CooldownEffectSpec;
	//

	FGameplayEffectSpecHandle CooldownGESpecHandle;

	FOnThisAbilityCooldownCompletedDelegate OnThisAbilityCooldownCompleted;
	
protected:
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<AProjectileHoming> HomingProjectileClass;

public:
	UMagicWandAbility();
	virtual ~UMagicWandAbility() override;

	void OnCooldownComplete(const FGameplayEffectRemovalInfo& GameplayEffectRemovalInfo) const;
	//virtual const FGameplayTagContainer* GetCooldownTags() const override;
	//virtual UGameplayEffect* GetCooldownGameplayEffect() const override;
	 virtual void ApplyCooldown(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
	 	const FGameplayAbilityActivationInfo ActivationInfo) const override;
	
protected:
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;

	virtual void Initialize(float InCooldown, UAbilitySystemComponent* InAbilitySystemComponent) override;
};
