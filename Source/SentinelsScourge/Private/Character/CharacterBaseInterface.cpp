// Copyright (c) Samarth Shroff. All Rights Reserved.
// This work is protected under applicable copyright laws in perpetuity.
// Licensed under the CC BY-NC-ND 4.0 License. See LICENSE file for details.

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

UAttributeSet* ICharacterBaseInterface::GetAttributeSetComponent() const
{
	return nullptr;
}
