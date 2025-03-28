// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "AttributeSet.h"
#include "VSPlayerAttributeSet.generated.h"

#define ALL_ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)

#define ATTRIBUTE_PROP_GETTER_N_INITTER_ACCESSORS(ClassName, PropertyName) \
GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)


/**
 * 
 */
UCLASS()
class VAMPIRESURVIVORCLONE_API UVSPlayerAttributeSet : public UAttributeSet
{
	GENERATED_BODY()

	// There should be an easy way to add attributes. Something like reading form a file and creating the variables at editor runtime.
	// Will check that later.
private:
	
	// Determines the current amount of HP for the character.
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Essential Attributes", meta = (AllowPrivateAccess = true))
	FGameplayAttributeData Health;

	// Determines the maximum amount of HP for the character.
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Essential Attributes", meta = (AllowPrivateAccess = true))
	FGameplayAttributeData MaxHealth;

	// Determines how much HP is generated for the character per second.
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Essential Attributes", meta = (AllowPrivateAccess = true))
	FGameplayAttributeData Recovery;

	// Determines the amount of reduced incoming damage.
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Essential Attributes", meta = (AllowPrivateAccess = true))
	FGameplayAttributeData Armor;

	// Modifies the movement speed of the character.
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Essential Attributes", meta = (AllowPrivateAccess = true))
	FGameplayAttributeData MoveSpeed;

	// Modifies the damage of all attacks.
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Essential Attributes", meta = (AllowPrivateAccess = true))
	FGameplayAttributeData Might;

	// Modifies the area of all attacks.
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Essential Attributes", meta = (AllowPrivateAccess = true))
	FGameplayAttributeData Area;

	// Modifies the movement speed of all projectiles.
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Essential Attributes", meta = (AllowPrivateAccess = true))
	FGameplayAttributeData Speed;

	// Modifies the duration of weapon effects.
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Essential Attributes", meta = (AllowPrivateAccess = true))
	FGameplayAttributeData Duration;

	// Determines the amount of extra projectiles weapons have.
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Essential Attributes", meta = (AllowPrivateAccess = true))
	FGameplayAttributeData Amount;

	// Modifies the duration of the cooldown between attacks.
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Essential Attributes", meta = (AllowPrivateAccess = true))
	FGameplayAttributeData Cooldown;

	// Modifies the chances of certain things, such as the drop chances of most Pickups and the chances of Treasure Chests being of higher quality.
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Essential Attributes", meta = (AllowPrivateAccess = true))
	FGameplayAttributeData Luck;

	// Modifies the amount of experience gained from collecting Experience Gems.
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Essential Attributes", meta = (AllowPrivateAccess = true))
	FGameplayAttributeData Growth;

	// Modifies the amount of gold gained from Pickups and Treasure Chests.
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Essential Attributes", meta = (AllowPrivateAccess = true))
	FGameplayAttributeData Greed;

	//	Modifies the enemies speed, health, quantity and frequency.
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Essential Attributes", meta = (AllowPrivateAccess = true))
	FGameplayAttributeData Curse;

	// 	Determines the radius inside which Experience Gems and Pickups are collected.
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Essential Attributes", meta = (AllowPrivateAccess = true))
	FGameplayAttributeData Magnet;

	// Determines the amount of Extra Lives the player has.
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Essential Attributes", meta = (AllowPrivateAccess = true))
	FGameplayAttributeData Revival;

	// Determines how many times the player can reroll level-up rewards.
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Essential Attributes", meta = (AllowPrivateAccess = true))
	FGameplayAttributeData Reroll;

	// Determines how many times the player can skip level-up rewards.
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Essential Attributes", meta = (AllowPrivateAccess = true))
	FGameplayAttributeData Skip;

	// Determines how many times the player can banish level-up rewards.
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Essential Attributes", meta = (AllowPrivateAccess = true))
	FGameplayAttributeData Banish;

	// Increases the quantity of enemy waves by a flat amount.
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Essential Attributes", meta = (AllowPrivateAccess = true))
	FGameplayAttributeData Charm;

	// Turns a percentage of enemy spawns unable to deal damage.
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Essential Attributes", meta = (AllowPrivateAccess = true))
	FGameplayAttributeData Defang;

	// 	Allows to Banish weapons from level-up choices or pick-ups from appearing before entering a stage. Used in the Collection menu.
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Essential Attributes", meta = (AllowPrivateAccess = true))
	FGameplayAttributeData Seal;
	
public:
	UVSPlayerAttributeSet();

	void Initialize();
	
	ATTRIBUTE_PROP_GETTER_N_INITTER_ACCESSORS(UVSPlayerAttributeSet, Health);
	float GetHealth() const;
	void SetHealth(float NewHealth) const;
	
	ALL_ATTRIBUTE_ACCESSORS(UVSPlayerAttributeSet, MaxHealth);
	// static FGameplayAttribute GetMaxHealthAttribute();
	// float GetMaxHealth() const;
	// void SetMaxHealth(float NewVal);
	// void InitMaxHealth(float NewVal);
	
	ALL_ATTRIBUTE_ACCESSORS(UVSPlayerAttributeSet, Recovery);
	ALL_ATTRIBUTE_ACCESSORS(UVSPlayerAttributeSet, Armor);
	ALL_ATTRIBUTE_ACCESSORS(UVSPlayerAttributeSet, MoveSpeed);
	ALL_ATTRIBUTE_ACCESSORS(UVSPlayerAttributeSet, Might);
	ALL_ATTRIBUTE_ACCESSORS(UVSPlayerAttributeSet, Area);
	ALL_ATTRIBUTE_ACCESSORS(UVSPlayerAttributeSet, Speed);
	ALL_ATTRIBUTE_ACCESSORS(UVSPlayerAttributeSet, Duration);
	ALL_ATTRIBUTE_ACCESSORS(UVSPlayerAttributeSet, Amount);
	ALL_ATTRIBUTE_ACCESSORS(UVSPlayerAttributeSet, Cooldown);
	ALL_ATTRIBUTE_ACCESSORS(UVSPlayerAttributeSet, Luck);
	ALL_ATTRIBUTE_ACCESSORS(UVSPlayerAttributeSet, Growth);
	ALL_ATTRIBUTE_ACCESSORS(UVSPlayerAttributeSet, Greed);
	ALL_ATTRIBUTE_ACCESSORS(UVSPlayerAttributeSet, Curse);
	ALL_ATTRIBUTE_ACCESSORS(UVSPlayerAttributeSet, Magnet);
	ALL_ATTRIBUTE_ACCESSORS(UVSPlayerAttributeSet, Revival);
	ALL_ATTRIBUTE_ACCESSORS(UVSPlayerAttributeSet, Reroll);
	ALL_ATTRIBUTE_ACCESSORS(UVSPlayerAttributeSet, Skip);
	ALL_ATTRIBUTE_ACCESSORS(UVSPlayerAttributeSet, Banish);
	ALL_ATTRIBUTE_ACCESSORS(UVSPlayerAttributeSet, Charm);
	ALL_ATTRIBUTE_ACCESSORS(UVSPlayerAttributeSet, Defang);
	ALL_ATTRIBUTE_ACCESSORS(UVSPlayerAttributeSet, Seal);	
};
