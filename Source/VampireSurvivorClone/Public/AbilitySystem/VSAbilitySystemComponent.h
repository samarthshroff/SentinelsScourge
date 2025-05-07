// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "VSAbilitySystemComponent.generated.h"

class UWeaponManager;
class UWeaponData;
struct FVSAbilityData;
/**
 * 
 */
UCLASS()
class VAMPIRESURVIVORCLONE_API UVSAbilitySystemComponent : public UAbilitySystemComponent
{
	GENERATED_BODY()

private:
	UPROPERTY()
	TObjectPtr<UWeaponManager> WeaponManager = nullptr; 
// private:
// 	TArray<FGameplayAbilitySpecHandle> AcquiredAbilities;

//private:
//	TMap<FGameplayTag, FGameplayAbilitySpecHandle> PossessedAbilities;

//public:
//	UPROPERTY(VisibleAnywhere)
//	TMap<FGameplayTag, FVSAbilityData> AcquiredAbilities;

public:
	// bool PossessAbility(FGameplayTag AbilityTag);
	// void AddCharacterAbilities(const TArray<TSubclassOf<UGameplayAbility>>& StartupAbilities);

	//void ActivateAcquiredAbilities();

	UVSAbilitySystemComponent(const FObjectInitializer& ObjectInitializer);
	void AcquireAbility(const FGameplayTag& AbilityTag);
	
	void Initialize(const TObjectPtr<UWeaponData>& WeaponData);
	UWeaponManager* GetWeaponManager();

	virtual FActiveGameplayEffectHandle ApplyGameplayEffectSpecToSelf(const FGameplayEffectSpec& GameplayEffect,
		FPredictionKey PredictionKey = FPredictionKey()) override;

private:
	void OnAbilityCooldownComplete(const FActiveGameplayEffect* ActiveGameplayEffect);
	// void OnAnyGameplayEffectRemoved(const FActiveGameplayEffect& ActiveGameplayEffect);
};

