// Copyright (c) Samarth Shroff. All Rights Reserved.
// This work is protected under applicable copyright laws in perpetuity.
// Licensed under the CC BY-NC-ND 4.0 License. See LICENSE file for details.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "AttributeSet.h"
#include "WeaponAttributeSet.generated.h"

#define ALL_ATTRIBUTE_ACCESSORS(ClassName, PropertyName)       \
	GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName)               \
	GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName)               \
	GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)

#define ATTRIBUTE_PROP_GETTER_N_INITTER_ACCESSORS(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName)             \
	GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)

/**
 * Weapons' Base Attribute Set.
 */
UCLASS()
class SENTINELSSCOURGE_API UWeaponAttributeSet : public UAttributeSet
{
	GENERATED_BODY()

public:
	// TODO - UNCOMMENT ReplicatedUsing TO RESUME ADDING MULTIPLAYER SUPPORT.
	// Determines the current level of the weapon.
	UPROPERTY(BlueprintReadOnly, /* ReplicatedUsing = OnRep_Health,*/ Category = "Essential Attributes")
	FGameplayAttributeData Level;

	// The damage dealt by a single projectile per hit. Modified by Might stat.
	UPROPERTY(BlueprintReadOnly, /* ReplicatedUsing = OnRep_MaxHealth,*/ Category = "Primary Attributes")
	FGameplayAttributeData Damage;

	// The base projectile speed of the weapon. Modified by Speed stat.
	UPROPERTY(BlueprintReadOnly, /* ReplicatedUsing = OnRep_MaxHealth,*/ Category = "Primary Attributes")
	FGameplayAttributeData Speed;

	// The duration of the weapon's effect. Modified by Duration stat.
	UPROPERTY(BlueprintReadOnly, /* ReplicatedUsing = OnRep_MaxHealth,*/ Category = "Primary Attributes")
	FGameplayAttributeData Duration;

	// The time required for the weapon to be used again. There is a trigger for the cooldown to start after a weapon's duration ends. Modified by Cooldown stat.
	UPROPERTY(BlueprintReadOnly, /* ReplicatedUsing = OnRep_MaxHealth,*/ Category = "Primary Attributes")
	FGameplayAttributeData Cooldown;

	// The time before the same enemy can be hit by the same projectile again. All delays refresh simultaneously as soon as one fully counts down.
	UPROPERTY(BlueprintReadOnly, /* ReplicatedUsing = OnRep_MaxHealth,*/ Category = "Primary Attributes")
	FGameplayAttributeData HitboxDelay;

	// The maximum amount of projectiles that can be on screen.
	UPROPERTY(BlueprintReadOnly, /* ReplicatedUsing = OnRep_MaxHealth,*/ Category = "Primary Attributes")
	FGameplayAttributeData PoolLimit;

	// Damage multiplier to critical hits.
	UPROPERTY(BlueprintReadOnly, /* ReplicatedUsing = OnRep_MaxHealth,*/ Category = "Primary Attributes")
	FGameplayAttributeData CritMulti;

	// The weight of the weapon in the pool of weapons and passive items.
	UPROPERTY(BlueprintReadOnly, /* ReplicatedUsing = OnRep_MaxHealth,*/ Category = "Primary Attributes")
	FGameplayAttributeData Rarity;

	// The base area of the weapon. Modified by Area stat.
	UPROPERTY(BlueprintReadOnly, /* ReplicatedUsing = OnRep_MaxHealth,*/ Category = "Primary Attributes")
	FGameplayAttributeData Area;

	// 	The amount of projectiles fired per use. Modified by Amount stat.
	UPROPERTY(BlueprintReadOnly, /* ReplicatedUsing = OnRep_MaxHealth,*/ Category = "Primary Attributes")
	FGameplayAttributeData Amount;

	// The number of enemies a single projectile can hit before being used up.
	UPROPERTY(BlueprintReadOnly, /* ReplicatedUsing = OnRep_MaxHealth,*/ Category = "Primary Attributes")
	FGameplayAttributeData Pierce;

	// The time required for an additional projectile to be fired between each Cooldown. Can overlap with another set of shots even before it finishes shooting.
	UPROPERTY(BlueprintReadOnly, /* ReplicatedUsing = OnRep_MaxHealth,*/ Category = "Primary Attributes")
	FGameplayAttributeData ProjectileInterval;

	// The knockback dealt multiplier of the weapon. Determines the strength of the knockback effect along with the enemy's knockback taken multiplier and movement speed.
	UPROPERTY(BlueprintReadOnly, /* ReplicatedUsing = OnRep_MaxHealth,*/ Category = "Primary Attributes")
	FGameplayAttributeData Knockback;

	// The chance of a special effect happening. Modified by Luck stat. Technically, Crit Chance is a separate stat but both have not been used at the same time yet.
	UPROPERTY(BlueprintReadOnly, /* ReplicatedUsing = OnRep_MaxHealth,*/ Category = "Primary Attributes")
	FGameplayAttributeData Chance;

	// Can the projectile be blocked by obstacles.
	UPROPERTY(BlueprintReadOnly, /* ReplicatedUsing = OnRep_MaxHealth,*/ Category = "Primary Attributes")
	FGameplayAttributeData BlockByWalls;

	// The highest level the weapon can be upgraded to.
	UPROPERTY(BlueprintReadOnly, /* ReplicatedUsing = OnRep_MaxHealth,*/ Category = "MaxValue Attributes")
	FGameplayAttributeData MaxLevel;

	UPROPERTY(BlueprintReadOnly, /* ReplicatedUsing = OnRep_MaxHealth,*/ Category = "MaxValue Attributes")
	FGameplayAttributeData MaxDamage;

	UPROPERTY(BlueprintReadOnly, /* ReplicatedUsing = OnRep_MaxHealth,*/ Category = "MaxValue Attributes")
	FGameplayAttributeData MaxArea;

	// UPROPERTY(BlueprintReadOnly, /* ReplicatedUsing = OnRep_MaxHealth,*/ Category="MaxValue Attributes")
	// FGameplayAttributeData MaxAmount;

	UPROPERTY(BlueprintReadOnly, /* ReplicatedUsing = OnRep_MaxHealth,*/ Category = "MaxValue Attributes")
	FGameplayAttributeData MaxDuration;

	UPROPERTY(BlueprintReadOnly, /* ReplicatedUsing = OnRep_MaxHealth,*/ Category = "MaxValue Attributes")
	FGameplayAttributeData MaxPierce;

	UPROPERTY(BlueprintReadOnly, /* ReplicatedUsing = OnRep_MaxHealth,*/ Category = "MaxValue Attributes")
	FGameplayAttributeData MaxSpeed;

	UPROPERTY(BlueprintReadOnly, /* ReplicatedUsing = OnRep_MaxHealth,*/ Category = "MaxValue Attributes")
	FGameplayAttributeData MaxChance;

private:
	virtual float ClampInclusive(float Value, float Min, float Max);

protected:
	virtual void PostGameplayEffectExecute(const struct FGameplayEffectModCallbackData &Data) override;
	virtual void PreAttributeChange(const FGameplayAttribute &Attribute, float &NewValue) override;

public:
	ALL_ATTRIBUTE_ACCESSORS(UWeaponAttributeSet, Level);
	ALL_ATTRIBUTE_ACCESSORS(UWeaponAttributeSet, Damage);
	ALL_ATTRIBUTE_ACCESSORS(UWeaponAttributeSet, Speed);
	ALL_ATTRIBUTE_ACCESSORS(UWeaponAttributeSet, Duration);
	ALL_ATTRIBUTE_ACCESSORS(UWeaponAttributeSet, Cooldown);
	ALL_ATTRIBUTE_ACCESSORS(UWeaponAttributeSet, HitboxDelay);
	ALL_ATTRIBUTE_ACCESSORS(UWeaponAttributeSet, PoolLimit);
	ALL_ATTRIBUTE_ACCESSORS(UWeaponAttributeSet, CritMulti);
	ALL_ATTRIBUTE_ACCESSORS(UWeaponAttributeSet, Rarity);
	ALL_ATTRIBUTE_ACCESSORS(UWeaponAttributeSet, Area);
	ALL_ATTRIBUTE_ACCESSORS(UWeaponAttributeSet, Amount);
	ALL_ATTRIBUTE_ACCESSORS(UWeaponAttributeSet, Pierce);
	ALL_ATTRIBUTE_ACCESSORS(UWeaponAttributeSet, ProjectileInterval);
	ALL_ATTRIBUTE_ACCESSORS(UWeaponAttributeSet, Knockback);
	ALL_ATTRIBUTE_ACCESSORS(UWeaponAttributeSet, Chance);

	ALL_ATTRIBUTE_ACCESSORS(UWeaponAttributeSet, MaxLevel);
	ALL_ATTRIBUTE_ACCESSORS(UWeaponAttributeSet, MaxDamage);
	ALL_ATTRIBUTE_ACCESSORS(UWeaponAttributeSet, MaxArea);
	ALL_ATTRIBUTE_ACCESSORS(UWeaponAttributeSet, MaxDuration);
	ALL_ATTRIBUTE_ACCESSORS(UWeaponAttributeSet, MaxPierce);
	ALL_ATTRIBUTE_ACCESSORS(UWeaponAttributeSet, MaxSpeed);
	ALL_ATTRIBUTE_ACCESSORS(UWeaponAttributeSet, MaxChance);

	ATTRIBUTE_PROP_GETTER_N_INITTER_ACCESSORS(UWeaponAttributeSet, BlockByWalls);
	void SetBlockByWalls(const float Value);
	void SetBlockByWalls(const bool bBlockByWalls);
	bool GetBlockByWalls() const;
};
