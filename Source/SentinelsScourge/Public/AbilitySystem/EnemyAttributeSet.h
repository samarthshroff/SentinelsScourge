// Copyright (c) Samarth Shroff. All Rights Reserved.
// This work is protected under applicable copyright laws in perpetuity.
// Licensed under the CC BY-NC-ND 4.0 License. See LICENSE file for details.

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "AbilitySystemComponent.h"
#include "EnemyAttributeSet.generated.h"

#define ALL_ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)

#define ATTRIBUTE_PROP_GETTER_N_INITTER_ACCESSORS(ClassName, PropertyName) \
GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)

/**
 * Enemy Actors' attribute set.
 */
UCLASS()
class SENTINELSSCOURGE_API UEnemyAttributeSet : public UAttributeSet
{
	GENERATED_BODY()

public:
	

	// Base Stats
	// Health describes how much damage is required to kill the enemy.
	UPROPERTY(BlueprintReadOnly, /* ReplicatedUsing = OnRep_Health,*/ Category="Base Attributes")
	FGameplayAttributeData Health;

	// Power describes how much damage the enemy does to the player upon coming in contact with them before modifications, such as Armor.
	UPROPERTY(BlueprintReadOnly, /* ReplicatedUsing = OnRep_Health,*/ Category="Base Attributes")
	FGameplayAttributeData Power;

	// Speed, describes how fast the enemy moves.
	UPROPERTY(BlueprintReadOnly, /* ReplicatedUsing = OnRep_Health,*/ Category="Base Attributes")
	FGameplayAttributeData Speed;

	// Knockback is a multiplier for the strength of the pushing effect when hit by the player's weapons.
	UPROPERTY(BlueprintReadOnly, /* ReplicatedUsing = OnRep_Health,*/ Category="Base Attributes")
	FGameplayAttributeData Knockback;

	// XP describes how much experience the enemy grants when killed.
	UPROPERTY(BlueprintReadOnly, /* ReplicatedUsing = OnRep_Health,*/ Category="Base Attributes")
	FGameplayAttributeData XP;

	UPROPERTY(BlueprintReadOnly, /* ReplicatedUsing = OnRep_Health,*/ Category="Base Attributes")
	FGameplayAttributeData MaxKnockback;

	// Resistance Stats
	// Freeze resistance prevents the enemy from being frozen by the player. It is given as a numerical value.
	// If the enemy's freeze resistance is higher than freeze chance of the weapon they were hit by it will not be frozen.
	// Freeze from Orologion goes through freeze resistance.
	UPROPERTY(BlueprintReadOnly, /* ReplicatedUsing = OnRep_Health,*/ Category="Resistance Attributes")
	FGameplayAttributeData FreezeResistance;

	// Kill resistance grants immunity to effects that instantly defeat an enemy by dealing damage to
	// them equal to their maximum health. Instant kill can be applied by Pentagram, Gorgeous Moon and Rosary.
	UPROPERTY(BlueprintReadOnly, /* ReplicatedUsing = OnRep_Health,*/ Category="Resistance Attributes")
	FGameplayAttributeData KillResistance;

	// Debuff resistance grants an immunity to effects that weaken the affected enemy upon hit.
	// Effects classified as debuffs are the knockback and freeze resistance reductions from Garlic and Soul Eater,
	// and the slow effect from Mannajja.
	UPROPERTY(BlueprintReadOnly, /* ReplicatedUsing = OnRep_Health,*/ Category="Resistance Attributes")
	FGameplayAttributeData DebuffResistance;

	UPROPERTY(BlueprintReadOnly, /* ReplicatedUsing = OnRep_Health,*/ Category="Resistance Attributes")
	FGameplayAttributeData DefangResistance;

	// Skills Stats

	// HP x Level multiplies the enemy's health based on the player's level.
	// This is applied the moment the enemy was spawned, and will not be updated in case the player gains levels while it's alive.
	UPROPERTY(BlueprintReadOnly, /* ReplicatedUsing = OnRep_Health,*/ Category="Skills Attributes")
	FGameplayAttributeData HPxLevel;

	// Causes the enemy to only move in a straight line, instead of continuously homing to the player.
	UPROPERTY(BlueprintReadOnly, /* ReplicatedUsing = OnRep_Health,*/ Category="Skills Attributes")
	FGameplayAttributeData FixedDirection;

	// Also known as "Medusa". Causes the enemy to move in a wavy pattern.
	UPROPERTY(BlueprintReadOnly, /* ReplicatedUsing = OnRep_Health,*/ Category="Skills Attributes")
	FGameplayAttributeData Floaty;

public:
	UEnemyAttributeSet();
	
	ALL_ATTRIBUTE_ACCESSORS(UEnemyAttributeSet, Health);
	ALL_ATTRIBUTE_ACCESSORS(UEnemyAttributeSet, Power);
	ALL_ATTRIBUTE_ACCESSORS(UEnemyAttributeSet, Speed);
	ALL_ATTRIBUTE_ACCESSORS(UEnemyAttributeSet, Knockback);
	ALL_ATTRIBUTE_ACCESSORS(UEnemyAttributeSet, XP);
	ALL_ATTRIBUTE_ACCESSORS(UEnemyAttributeSet, MaxKnockback);
	ALL_ATTRIBUTE_ACCESSORS(UEnemyAttributeSet, FreezeResistance);
	ALL_ATTRIBUTE_ACCESSORS(UEnemyAttributeSet, KillResistance);
	ALL_ATTRIBUTE_ACCESSORS(UEnemyAttributeSet, DebuffResistance);
	ALL_ATTRIBUTE_ACCESSORS(UEnemyAttributeSet, DefangResistance);
	ALL_ATTRIBUTE_ACCESSORS(UEnemyAttributeSet, HPxLevel);
	ALL_ATTRIBUTE_ACCESSORS(UEnemyAttributeSet, FixedDirection);
	ALL_ATTRIBUTE_ACCESSORS(UEnemyAttributeSet, Floaty);
	
};
