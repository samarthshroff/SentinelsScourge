// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "ActiveGameplayEffectHandle.h"
#include "CharacterBaseInterface.h"
#include "GameFramework/Character.h"
#include "CharacterBase.generated.h"

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
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY()
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent;

	UPROPERTY()
	TObjectPtr<UAttributeSet> AttributeSet;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Attributes", meta = (AllowPrivateAccess = true))
	TSubclassOf<UGameplayEffect> DefaultAttributes;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Attributes", meta = (AllowPrivateAccess = true))
	TSubclassOf<UGameplayEffect> BonusAttributes;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Attributes", meta = (AllowPrivateAccess = true))
	TSubclassOf<UGameplayEffect> EssentialAttributes;
	
	FActiveGameplayEffectHandle ApplyEffectToSelf(TSubclassOf<UGameplayEffect> AttributesGameplayEffect, float Level);
	void InitializeAttributes();

public:	
	// Called every frame
	//virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
};
