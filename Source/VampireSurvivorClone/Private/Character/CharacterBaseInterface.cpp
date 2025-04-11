// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/CharacterBaseInterface.h"

#include "GameplayTagContainer.h"

// Add default functionality here for any ICharacterBaseInterface functions that are not pure virtual.
int32 ICharacterBaseInterface::GetCharacterLevel()
{
	return 0;
}

FGameplayTag ICharacterBaseInterface::GetCharacterTag() const
{
	return FGameplayTag::EmptyTag;
}
