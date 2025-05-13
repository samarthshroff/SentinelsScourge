// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "CharacterBaseInterface.generated.h"

struct FGameplayAbilitySpecHandle;
struct FGameplayTag;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnCharacterDestroyedDelegate, AActor*, Actor);

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UCharacterBaseInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class VAMPIRESURVIVORCLONE_API ICharacterBaseInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	FOnCharacterDestroyedDelegate OnCharacterDestroyed;
	
public:
	virtual int32 GetCharacterLevel() const;
	virtual FGameplayTag GetCharacterTag() const;
	virtual int GetWeaponLevel(const FGameplayTag& AbilityTag) const;
	virtual void GiveAbility(const FGameplayTag& AbilityTag);
	virtual bool TagExactExistsInAbilityComponent(const FGameplayTag InTag) const;
	virtual bool IsCharacterAlive() const;
};
