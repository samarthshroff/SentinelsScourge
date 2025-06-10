// Copyright (c) Samarth Shroff. All Rights Reserved.
// This work is protected under applicable copyright laws in perpetuity.
// Licensed under the CC BY-NC-ND 4.0 License. See LICENSE file for details.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "AttributeSet.h"
#include "PlayerAttributeSet.generated.h"

#define ALL_ATTRIBUTE_ACCESSORS(ClassName, PropertyName)       \
	GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName)               \
	GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName)               \
	GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)

#define ATTRIBUTE_PROP_GETTER_N_INITTER_ACCESSORS(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName)             \
	GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)

// Resolve to a type of function pointer a delegate would use for function signature T.
template <class T>
using TStaticFuncPtr = typename TBaseStaticDelegateInstance<T, FDefaultDelegateUserPolicy>::FFuncPtr;

/**
 * Player Attribute Set.
 */
UCLASS()
class SENTINELSSCOURGE_API UPlayerAttributeSet : public UAttributeSet
{
	GENERATED_BODY()

	// There should be an easy way to add attributes. Something like reading form a file and creating the variables at editor runtime.
	// Will check that later.
public:
	// TODO - UNCOMMENT ReplicatedUsing TO RESUME ADDING MULTIPLAYER SUPPORT.
	// Determines the current amount of HP for the character.
	UPROPERTY(BlueprintReadOnly, /* ReplicatedUsing = OnRep_Health,*/ Category = "Essential Attributes")
	FGameplayAttributeData Health;

	UPROPERTY(BlueprintReadOnly, /* ReplicatedUsing = OnRep_Seal,*/ Category = "Essential Attributes")
	FGameplayAttributeData Level;

	UPROPERTY(BlueprintReadOnly, /* ReplicatedUsing = OnRep_Seal,*/ Category = "Essential Attributes")
	FGameplayAttributeData XP;

	UPROPERTY(BlueprintReadOnly, /* ReplicatedUsing = OnRep_Seal,*/ Category = "Essential Attributes")
	FGameplayAttributeData MaxXP;

	// Determines the maximum amount of HP for the character.
	UPROPERTY(BlueprintReadOnly, /* ReplicatedUsing = OnRep_MaxHealth,*/ Category = "Primary Attributes")
	FGameplayAttributeData MaxHealth;

	// Determines how much HP is generated for the character per second.
	UPROPERTY(BlueprintReadOnly, /* ReplicatedUsing = OnRep_Recovery,*/ Category = "Primary Attributes")
	FGameplayAttributeData Recovery;

	// Determines the amount of reduced incoming damage.
	UPROPERTY(BlueprintReadOnly, /* ReplicatedUsing = OnRep_Armor,*/ Category = "Primary Attributes")
	FGameplayAttributeData Armor;

	// Modifies the movement speed of the character.
	UPROPERTY(BlueprintReadOnly, /* ReplicatedUsing = OnRep_MoveSpeed,*/ Category = "Primary Attributes")
	FGameplayAttributeData MoveSpeed;

	// Modifies the damage of all attacks.
	UPROPERTY(BlueprintReadOnly, /* ReplicatedUsing = OnRep_Might,*/ Category = "Primary Attributes")
	FGameplayAttributeData Might;

	// Modifies the area of all attacks.
	UPROPERTY(BlueprintReadOnly, /* ReplicatedUsing = OnRep_Area,*/ Category = "Primary Attributes")
	FGameplayAttributeData Area;

	// Modifies the movement speed of all projectiles.
	UPROPERTY(BlueprintReadOnly, /* ReplicatedUsing = OnRep_Speed,*/ Category = "Primary Attributes")
	FGameplayAttributeData Speed;

	// Modifies the duration of weapon effects.
	UPROPERTY(BlueprintReadOnly, /* ReplicatedUsing = OnRep_Duration,*/ Category = "Primary Attributes")
	FGameplayAttributeData Duration;

	// Determines the amount of extra projectiles weapons have.
	UPROPERTY(BlueprintReadOnly, /* ReplicatedUsing = OnRep_Amount,*/ Category = "Primary Attributes")
	FGameplayAttributeData Amount;

	// Modifies the duration of the cooldown between attacks.
	UPROPERTY(BlueprintReadOnly, /* ReplicatedUsing = OnRep_Cooldown,*/ Category = "Primary Attributes")
	FGameplayAttributeData Cooldown;

	// Modifies the chances of certain things, such as the drop chances of most Pickups and the chances of Treasure Chests being of higher quality.
	UPROPERTY(BlueprintReadOnly, /* ReplicatedUsing = OnRep_Luck,*/ Category = "Primary Attributes")
	FGameplayAttributeData Luck;

	// Modifies the amount of experience gained from collecting Experience Gems.
	UPROPERTY(BlueprintReadOnly, /* ReplicatedUsing = OnRep_Growth,*/ Category = "Primary Attributes")
	FGameplayAttributeData Growth;

	// Modifies the amount of gold gained from Pickups and Treasure Chests.
	UPROPERTY(BlueprintReadOnly, /* ReplicatedUsing = OnRep_Greed,*/ Category = "Primary Attributes")
	FGameplayAttributeData Greed;

	//	Modifies the enemies speed, health, quantity and frequency.
	UPROPERTY(BlueprintReadOnly, /* ReplicatedUsing = OnRep_Curse,*/ Category = "Primary Attributes")
	FGameplayAttributeData Curse;

	// 	Determines the radius inside which Experience Gems and Pickups are collected.
	UPROPERTY(BlueprintReadOnly, /* ReplicatedUsing = OnRep_Magnet,*/ Category = "Primary Attributes")
	FGameplayAttributeData Magnet;

	// Determines the amount of Extra Lives the player has.
	UPROPERTY(BlueprintReadOnly, /* ReplicatedUsing = OnRep_Revival,*/ Category = "Primary Attributes")
	FGameplayAttributeData Revival;

	// Determines how many times the player can reroll level-up rewards.
	UPROPERTY(BlueprintReadOnly, /* ReplicatedUsing = OnRep_Reroll,*/ Category = "Primary Attributes")
	FGameplayAttributeData Reroll;

	// Determines how many times the player can skip level-up rewards.
	UPROPERTY(BlueprintReadOnly, /* ReplicatedUsing = OnRep_Skip,*/ Category = "Primary Attributes")
	FGameplayAttributeData Skip;

	// Determines how many times the player can banish level-up rewards.
	UPROPERTY(BlueprintReadOnly, /* ReplicatedUsing = OnRep_Banish,*/ Category = "Primary Attributes")
	FGameplayAttributeData Banish;

	// Increases the quantity of enemy waves by a flat amount.
	UPROPERTY(BlueprintReadOnly, /* ReplicatedUsing = OnRep_Charm,*/ Category = "Primary Attributes")
	FGameplayAttributeData Charm;

	// Turns a percentage of enemy spawns unable to deal damage.
	UPROPERTY(BlueprintReadOnly, /* ReplicatedUsing = OnRep_Defang,*/ Category = "Primary Attributes")
	FGameplayAttributeData Defang;

	// 	Allows to Banish weapons from level-up choices or pick-ups from appearing before entering a stage. Used in the Collection menu.
	UPROPERTY(BlueprintReadOnly, /* ReplicatedUsing = OnRep_Seal,*/ Category = "Primary Attributes")
	FGameplayAttributeData Seal;

	// TODO - UNCOMMENT THIS TO RESUME ADDING MULTIPLAYER SUPPORT.
	// virtual void GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const override;

	ALL_ATTRIBUTE_ACCESSORS(UPlayerAttributeSet, Health);
	ALL_ATTRIBUTE_ACCESSORS(UPlayerAttributeSet, MaxHealth);
	ALL_ATTRIBUTE_ACCESSORS(UPlayerAttributeSet, Level);
	ALL_ATTRIBUTE_ACCESSORS(UPlayerAttributeSet, XP);
	ALL_ATTRIBUTE_ACCESSORS(UPlayerAttributeSet, MaxXP);
	ALL_ATTRIBUTE_ACCESSORS(UPlayerAttributeSet, Recovery);
	ALL_ATTRIBUTE_ACCESSORS(UPlayerAttributeSet, Armor);
	ALL_ATTRIBUTE_ACCESSORS(UPlayerAttributeSet, MoveSpeed);
	ALL_ATTRIBUTE_ACCESSORS(UPlayerAttributeSet, Might);
	ALL_ATTRIBUTE_ACCESSORS(UPlayerAttributeSet, Area);
	ALL_ATTRIBUTE_ACCESSORS(UPlayerAttributeSet, Speed);
	ALL_ATTRIBUTE_ACCESSORS(UPlayerAttributeSet, Duration);
	ALL_ATTRIBUTE_ACCESSORS(UPlayerAttributeSet, Amount);
	ALL_ATTRIBUTE_ACCESSORS(UPlayerAttributeSet, Cooldown);
	ALL_ATTRIBUTE_ACCESSORS(UPlayerAttributeSet, Luck);
	ALL_ATTRIBUTE_ACCESSORS(UPlayerAttributeSet, Growth);
	ALL_ATTRIBUTE_ACCESSORS(UPlayerAttributeSet, Greed);
	ALL_ATTRIBUTE_ACCESSORS(UPlayerAttributeSet, Curse);
	ALL_ATTRIBUTE_ACCESSORS(UPlayerAttributeSet, Magnet);
	ALL_ATTRIBUTE_ACCESSORS(UPlayerAttributeSet, Revival);
	ALL_ATTRIBUTE_ACCESSORS(UPlayerAttributeSet, Reroll);
	ALL_ATTRIBUTE_ACCESSORS(UPlayerAttributeSet, Skip);
	ALL_ATTRIBUTE_ACCESSORS(UPlayerAttributeSet, Banish);
	ALL_ATTRIBUTE_ACCESSORS(UPlayerAttributeSet, Charm);
	ALL_ATTRIBUTE_ACCESSORS(UPlayerAttributeSet, Defang);
	ALL_ATTRIBUTE_ACCESSORS(UPlayerAttributeSet, Seal);

	TMap<FGameplayTag, TStaticFuncPtr<FGameplayAttribute()>> AllAttributes;

protected:
	virtual void PostGameplayEffectExecute(const struct FGameplayEffectModCallbackData &Data) override;
	virtual void PreAttributeChange(const FGameplayAttribute &Attribute, float &NewValue) override;

public:
	UPlayerAttributeSet();

	void UpdateXPs();

	// void IncrementLevel(int32 NewLevel);

private:
	void UpdateMaxXPForLevel();

	// TODO - UNCOMMENT THIS TO RESUME ADDING MULTIPLAYER SUPPORT.
	/*private:
		// TODO - MAYBE WRITE A PYTHON SCRIPT TO GENERATE THE DECLARATION AND IMPLEMENTATION OF THESE ONREP FUNCTIONS.
		UFUNCTION()
		void OnRep_Health(const FGameplayAttributeData& OldValue) const;

		UFUNCTION()
		void OnRep_MaxHealth(const FGameplayAttributeData& OldValue) const;

		UFUNCTION()
		void OnRep_Recovery(const FGameplayAttributeData& OldValue) const;

		UFUNCTION()
		void OnRep_Armor(const FGameplayAttributeData& OldValue) const;

		UFUNCTION()
		void OnRep_MoveSpeed(const FGameplayAttributeData& OldValue) const;

		UFUNCTION()
		void OnRep_Might(const FGameplayAttributeData& OldValue) const;

		UFUNCTION()
		void OnRep_Area(const FGameplayAttributeData& OldValue) const;

		UFUNCTION()
		void OnRep_Speed(const FGameplayAttributeData& OldValue) const;

		UFUNCTION()
		void OnRep_Duration(const FGameplayAttributeData& OldValue) const;

		UFUNCTION()
		void OnRep_Amount(const FGameplayAttributeData& OldValue) const;

		UFUNCTION()
		void OnRep_Cooldown(const FGameplayAttributeData& OldValue) const;

		UFUNCTION()
		void OnRep_Luck(const FGameplayAttributeData& OldValue) const;

		UFUNCTION()
		void OnRep_Growth(const FGameplayAttributeData& OldValue) const;

		UFUNCTION()
		void OnRep_Greed(const FGameplayAttributeData& OldValue) const;

		UFUNCTION()
		void OnRep_Curse(const FGameplayAttributeData& OldValue) const;

		UFUNCTION()
		void OnRep_Magnet(const FGameplayAttributeData& OldValue) const;

		UFUNCTION()
		void OnRep_Revival(const FGameplayAttributeData& OldValue) const;

		UFUNCTION()
		void OnRep_Reroll(const FGameplayAttributeData& OldValue) const;

		UFUNCTION()
		void OnRep_Skip(const FGameplayAttributeData& OldValue) const;

		UFUNCTION()
		void OnRep_Banish(const FGameplayAttributeData& OldValue) const;

		UFUNCTION()
		void OnRep_Charm(const FGameplayAttributeData& OldValue) const;

		UFUNCTION()
		void OnRep_Defang(const FGameplayAttributeData& OldValue) const;

		UFUNCTION()
		void OnRep_Seal(const FGameplayAttributeData& OldValue) const;*/
};
