// Copyright (c) Samarth Shroff. All Rights Reserved.
// This work is protected under applicable copyright laws in perpetuity.
// Licensed under the CC BY-NC-ND 4.0 License. See LICENSE file for details.

#pragma once
#include "GameplayTagContainer.h"
#include "AbilitySystem/EnemyAttributeSet.h"
#include "EnemyMetaData.generated.h"

USTRUCT(BlueprintType)
struct SENTINELSSCOURGE_API FEnemyMetaData : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FGameplayTag EnemyTag;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float DistanceFromPlayerCharacter;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	double SpawnIntervalInSeconds;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float MinimumSpawnDistanceFromPlayer;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float MaximumSpawnDistanceFromPlayer;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int IntroduceFromHeroLevel;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSoftObjectPtr<USkeletalMesh> Mesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSoftClassPtr<UAnimInstance> AnimationBlueprint;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSoftObjectPtr<UAnimMontage> AnimationMontageDie;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<TSoftClassPtr<UGameplayEffect>> DefaultAttributes;

	FEnemyMetaData() = default;

	FEnemyMetaData(const FEnemyMetaData &Other) = default;

	FEnemyMetaData &operator=(const FEnemyMetaData &Other) = default;

	FEnemyMetaData(FEnemyMetaData &&Other) noexcept = default;

	FEnemyMetaData &operator=(FEnemyMetaData &&Other) noexcept = default;
};
