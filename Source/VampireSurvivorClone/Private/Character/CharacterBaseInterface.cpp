// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/CharacterBaseInterface.h"

#include "GameplayTagContainer.h"

// Add default functionality here for any ICharacterBaseInterface functions that are not pure virtual.
int32 ICharacterBaseInterface::GetCharacterLevel() const
{
	return 0;
}

FGameplayTag ICharacterBaseInterface::GetCharacterTag() const
{
	return FGameplayTag::EmptyTag;
}

int ICharacterBaseInterface::GetWeaponLevel(const FGameplayTag& AbilityTag) const
{
	return 0;
}

void ICharacterBaseInterface::GiveAbility(const FGameplayTag& AbilityTag)
{
}

bool ICharacterBaseInterface::TagExactExistsInAbilityComponent(const FGameplayTag InTag) const
{
	return false;
}

bool ICharacterBaseInterface::IsCharacterAlive() const
{
	return false;
}
