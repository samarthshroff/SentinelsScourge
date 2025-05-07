// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "ActiveGameplayEffectHandle.h"
#include "CharacterBaseInterface.h"
#include "GameFramework/Character.h"
#include "CharacterBase.generated.h"

class UWeaponData;
struct FGameplayAbilitySpecHandle;
class UGameplayAbility;
class UGameplayEffect;
class UAttributeSet;
class UVSAbilitySystemComponent;
class UCameraComponent;
class USpringArmComponent;

UCLASS()
class VAMPIRESURVIVORCLONE_API ACharacterBase : public ACharacter, public IAbilitySystemInterface, public ICharacterBaseInterface
{
	GENERATED_BODY()

private:
	// Need Effect handles for default as well as essential as all the
	// attributes should be reset after each run (game win or game lose.)
	FActiveGameplayEffectHandle DefaultAttributesEffectHandle;
	FActiveGameplayEffectHandle EssentialAttributesEffectHandle;
	FActiveGameplayEffectHandle BonusAttributesEffectHandle;
	FActiveGameplayEffectHandle PowerUpsAttributesEffectHandle;
	FActiveGameplayEffectHandle PassiveItemsAttributesEffectHandle;
	FActiveGameplayEffectHandle ArcanasAttributesEffectHandle;

public:
	// Sets default values for this character's properties
	ACharacterBase();
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	virtual UAttributeSet* GetAttributeSetComponent() const;

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Abilities", meta=(AllowPrivateAccess=true))
	TArray<TSubclassOf<UGameplayAbility>> StartupAbilities;
	
	UPROPERTY()
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent;

	UPROPERTY()
	TObjectPtr<UAttributeSet> AttributeSet;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Attributes", meta = (AllowPrivateAccess = true))
	TSubclassOf<UGameplayEffect> DefaultAttributes;

	//TODO - Assignment should happen at the hero selection level or based on the hero selected.
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Attributes", meta = (AllowPrivateAccess = true))
	TSubclassOf<UGameplayEffect> BonusAttributes;

	// Based on the attributes set from default and bonus. Like health (for now)
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Attributes", meta = (AllowPrivateAccess = true))
	TSubclassOf<UGameplayEffect> EssentialAttributes;

	UPROPERTY(EditDefaultsOnly, Category="Weapon")
	TObjectPtr<UWeaponData> WeaponDataAsset;
	
public:	

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	FActiveGameplayEffectHandle ApplyEffectToSelf(const TSubclassOf<UGameplayEffect>& AttributesGameplayEffect, float Level) const;
	void InitializeAttributes();
	virtual void InitAbilityActorInfo();

	virtual void GiveAbility(const FGameplayTag& AbilityTag) override;
};
