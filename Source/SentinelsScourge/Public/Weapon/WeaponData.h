// Copyright (c) Samarth Shroff. All Rights Reserved.
// This work is protected under applicable copyright laws in perpetuity.
// Licensed under the CC BY-NC-ND 4.0 License. See LICENSE file for details.

#pragma once

#include "GameplayAbilitySpecHandle.h"
#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "GameplayTagContainer.h"
#include "WeaponData.generated.h"

class UGameplayEffect;
class UWeaponAttributeSet;
class USSGameplayAbility;

USTRUCT(BlueprintType)
struct SENTINELSSCOURGE_API FWeaponMetaData //: public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
	FGameplayTag Category;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
	FGameplayTag Name;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
	TSoftClassPtr<USSGameplayAbility> AbilityClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
	TSoftClassPtr<UWeaponAttributeSet> AttributeSet;

	// This Gameplay Effects that has the initial default values for weapon attribute
	// will also have the next attribute to apply in the components section.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
	TSoftClassPtr<UGameplayEffect> DefaultAttributes;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon | Level Up")
	TArray<FText> LevelUpInfo;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon | UI")
	TSoftObjectPtr<UStaticMesh> UIIcon;

	// You can have a single condition or an array for "AND" logic
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Instanced, Category = "Weapon | Unlocks")
	TArray<class UBaseUnlockCondition *> UnlockConditions; // Array for multiple conditions (all must be met for unlock)

	// Optional: FText to display the condition string when locked
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon | Unlocks")
	FText UnlockDescription; // This will show "Kill 100 Skeletons" or "Survive 10 mins"

	// Optional: Whether this item is unlocked by default or requires conditions
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon | Unlocks")
	bool bUnlockedByDefault;

public:
	FWeaponMetaData() = default;

	FWeaponMetaData(const FWeaponMetaData &Other) = default;

	FWeaponMetaData &operator=(const FWeaponMetaData &Other) = default;

	FWeaponMetaData(FWeaponMetaData &&Other) noexcept = default;

	FWeaponMetaData &operator=(FWeaponMetaData &&Other) noexcept = default;
};

UCLASS()
class SENTINELSSCOURGE_API UWeaponData : public UDataAsset
{
	GENERATED_BODY()
public:
	TOptional<const FWeaponMetaData> FindAbilityDataForTag(const FGameplayTag &WeaponTag, bool bLogNotFound = true);

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TArray<FWeaponMetaData> WeaponsInfo;
};
