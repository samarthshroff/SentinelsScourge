// Copyright (c) Samarth Shroff. All Rights Reserved.
// This work is protected under applicable copyright laws in perpetuity.
// Licensed under the CC BY-NC-ND 4.0 License. See LICENSE file for details.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "UObject/Object.h"
#include "GameBoon.generated.h"

class UGameplayEffect;
/**
 *
 */
USTRUCT(BlueprintType)
struct SENTINELSSCOURGE_API FGameBoon
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
	FGameplayTag Category;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
	FGameplayTag Name;

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
	FGameBoon() = default;

	FGameBoon(const FGameBoon &Other) = default;

	FGameBoon &operator=(const FGameBoon &Other) = default;

	FGameBoon(FGameBoon &&Other) noexcept = default;

	FGameBoon &operator=(FGameBoon &&Other) noexcept = default;
};
