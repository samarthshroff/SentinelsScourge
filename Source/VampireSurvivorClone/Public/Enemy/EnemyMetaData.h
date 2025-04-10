#pragma once
#include "GameplayTagContainer.h"
#include "../WeaponType.h"

#include "EnemyMetaData.generated.h"

USTRUCT(BlueprintType)
struct VAMPIRESURVIVORCLONE_API FEnemyMetaData : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FGameplayTag EnemyTag;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSoftObjectPtr<USkeletalMesh> Mesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Speed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Health;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Damage;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float DistanceFromPlayerCharacter;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UWeaponType WeaponType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	double SpawnIntervalInSeconds;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSoftClassPtr<UAnimInstance> AnimationBlueprint;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float MinimumSpawnDistanceFromPlayer;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float MaximumSpawnDistanceFromPlayer;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int IntroduceFromHeroLevel;
	
	FEnemyMetaData() = default;
		
	FEnemyMetaData(const FEnemyMetaData& Other)
	{
		EnemyTag = Other.EnemyTag;
		Mesh = Other.Mesh;
		Speed = Other.Speed;
		Health = Other.Health;
		Damage = Other.Damage;
		IntroduceFromHeroLevel = Other.IntroduceFromHeroLevel;
		DistanceFromPlayerCharacter = Other.DistanceFromPlayerCharacter;
		WeaponType = Other.WeaponType;
		SpawnIntervalInSeconds = Other.SpawnIntervalInSeconds;
		AnimationBlueprint = Other.AnimationBlueprint;
		MinimumSpawnDistanceFromPlayer = Other.MinimumSpawnDistanceFromPlayer;
		MaximumSpawnDistanceFromPlayer = Other.MaximumSpawnDistanceFromPlayer;
	}
	
	FEnemyMetaData& operator=(const FEnemyMetaData& Other)
	{
		if (this != &Other)
		{
			EnemyTag = Other.EnemyTag;
			Mesh = Other.Mesh;
			Speed = Other.Speed;
			Health = Other.Health;
			Damage = Other.Damage;
			IntroduceFromHeroLevel = Other.IntroduceFromHeroLevel;
			DistanceFromPlayerCharacter = Other.DistanceFromPlayerCharacter;
			WeaponType = Other.WeaponType;
			SpawnIntervalInSeconds = Other.SpawnIntervalInSeconds;
			AnimationBlueprint = Other.AnimationBlueprint;
			MinimumSpawnDistanceFromPlayer = Other.MinimumSpawnDistanceFromPlayer;
			MaximumSpawnDistanceFromPlayer = Other.MaximumSpawnDistanceFromPlayer;
		}
		return *this;
	}
	
	FEnemyMetaData(FEnemyMetaData&& Other) noexcept
	{
		EnemyTag = Other.EnemyTag;
		Mesh=MoveTemp(Other.Mesh);
		Speed=Other.Speed;
		Health=Other.Health;
		Damage=Other.Damage;
		IntroduceFromHeroLevel = Other.IntroduceFromHeroLevel;
		DistanceFromPlayerCharacter=Other.DistanceFromPlayerCharacter;
		WeaponType=Other.WeaponType;
		SpawnIntervalInSeconds=Other.SpawnIntervalInSeconds;
		AnimationBlueprint = MoveTemp(Other.AnimationBlueprint);
		MinimumSpawnDistanceFromPlayer = Other.MinimumSpawnDistanceFromPlayer;
		MaximumSpawnDistanceFromPlayer = Other.MaximumSpawnDistanceFromPlayer;
	}
	
	FEnemyMetaData& operator=(FEnemyMetaData&& Other) noexcept
	{
		if (this != &Other)
		{
			EnemyTag = Other.EnemyTag;
			Mesh=MoveTemp(Other.Mesh);
			Speed=Other.Speed;
			Health=Other.Health;
			Damage=Other.Damage;
			IntroduceFromHeroLevel = Other.IntroduceFromHeroLevel;
			DistanceFromPlayerCharacter=Other.DistanceFromPlayerCharacter;
			WeaponType=Other.WeaponType;
			SpawnIntervalInSeconds=Other.SpawnIntervalInSeconds;
			AnimationBlueprint = MoveTemp(Other.AnimationBlueprint);
			MinimumSpawnDistanceFromPlayer = Other.MinimumSpawnDistanceFromPlayer;
			MaximumSpawnDistanceFromPlayer = Other.MaximumSpawnDistanceFromPlayer;
		}
		return *this;
	}
};
