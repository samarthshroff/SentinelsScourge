// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SSGameplayAbility.h"
#include "SSGameplayAbilityInterface.h"
#include "MagicWandAbility.generated.h"

class UAbilityTask_HomingProjectile;
class AProjectileHoming;

DECLARE_DELEGATE(FOnThisAbilityCooldownCompletedDelegate);

/**
 * Magic wand weapon ability
 */
UCLASS()
class SENTINELSSCOURGE_API UMagicWandAbility : public USSGameplayAbility
{
	GENERATED_BODY()

private:
	UPROPERTY()
	TObjectPtr<UAbilityTask_HomingProjectile> HomingProjectileTask;

	TOptional<float> Cooldown;

	// Event executed on cooldown expiration so that non-const CommitCooldown function can be
	// called which otherwise is not callable directly from the Cooldown const listener.
	FOnThisAbilityCooldownCompletedDelegate OnThisAbilityCooldownCompleted;

protected:
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<AProjectileHoming> HomingProjectileClass;

public:
	UMagicWandAbility();
	virtual ~UMagicWandAbility() override;

	void OnCooldownComplete(const FGameplayEffectRemovalInfo &GameplayEffectRemovalInfo) const;

	virtual void ApplyCooldown(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo *ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo) const override;

protected:
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo *ActorInfo,
								 const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData *TriggerEventData) override;

	virtual void Initialize(float InCooldown) override;
};
