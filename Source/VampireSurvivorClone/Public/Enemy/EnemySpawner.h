// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EnemyMetaData.h"
#include "GameplayTagContainer.h"
#include "../Player/PlayerCharacter.h"
#include "Engine/AssetManager.h"
#include "Engine/StreamableManager.h"
#include "GameFramework/Actor.h"
#include "EnemySpawner.generated.h"

class AEnemyCharacterBase;

DECLARE_DELEGATE_TwoParams(FOnAssetsLoadedDelegate, const FGameplayTag&, double);

// USTRUCT()
// struct FEnemySpawnInfo
// {
// 	GENERATED_BODY()
//
// 	FGameplayTag Tag;
// 	double StartTimeInSeconds;
// 	double SpawnIntervalInSeconds;
// 	int32 IntroduceFromHeroPlayerLevel;
//
// 	FEnemySpawnInfo(const FGameplayTag& Tag, const double SpawnIntervalInSeconds,
// 		const int32 IntroduceFromHeroPlayerLevel)
// 		: Tag(Tag),
// 		  StartTimeInSeconds(-1.0),
// 		  SpawnIntervalInSeconds(SpawnIntervalInSeconds),
// 		  IntroduceFromHeroPlayerLevel(IntroduceFromHeroPlayerLevel)
// 	{
// 	}
// };

UCLASS()
class UEnemyData : public UObject
{
	GENERATED_BODY()
public:
	UPROPERTY()
	TObjectPtr<USkeletalMesh> SkeletalMesh;

	UPROPERTY()
	TObjectPtr<UClass> AnimInstance;

	TUniquePtr<FEnemyMetaData> MetaData;

	bool bIsLoaded;

	FOnAssetsLoadedDelegate OnAssetsLoaded;

	double StartTimeInSeconds;

	void OnLoad()
	{
		if (SkeletalMesh != nullptr && AnimInstance != nullptr)
		{
			UE_LOG(LogTemp, Log, TEXT("Enemy Data loaded for %s"), *(MetaData->EnemyTag.ToString()));
			bIsLoaded = true;
			OnAssetsLoaded.ExecuteIfBound(MetaData->EnemyTag, MetaData->SpawnIntervalInSeconds);
		}
	}

	void Initialize()
	{
		FStreamableManager& Manager = UAssetManager::GetStreamableManager();

		if (MetaData->Mesh.IsValid())
		{
			UE_LOG(LogTemp, Log, TEXT("Mesh already valid: %s"), *MetaData->Mesh.ToSoftObjectPath().ToString());
			SkeletalMesh = MetaData->Mesh.Get();
			OnLoad();
		}
		else
		{
			UE_LOG(LogTemp, Log, TEXT("Mesh Path: %s"), *MetaData->Mesh.ToSoftObjectPath().ToString());
			Manager.RequestAsyncLoad(MetaData->Mesh.ToSoftObjectPath(),
				FStreamableDelegate::CreateLambda([this]()
				{
					if (MetaData->Mesh.IsValid())
					{
						this->SkeletalMesh = MetaData->Mesh.Get();
						OnLoad();
					}
				}));
		}

		if (MetaData->AnimationBlueprint.IsValid())
		{
			UE_LOG(LogTemp, Log, TEXT("Anim already valid: %s"), *MetaData->AnimationBlueprint.ToSoftObjectPath().ToString());
			AnimInstance = MetaData->AnimationBlueprint.Get();
			OnLoad();
		}
		else
		{
			if (!MetaData->AnimationBlueprint.IsNull())
			{
				UE_LOG(LogTemp, Log, TEXT("Anim Path: %s"), *MetaData->AnimationBlueprint.ToSoftObjectPath().ToString());
				Manager.RequestAsyncLoad(MetaData->AnimationBlueprint.ToSoftObjectPath(),
						FStreamableDelegate::CreateWeakLambda(this, [this]()
						{
							if (MetaData->AnimationBlueprint.IsValid())
							{
								this->AnimInstance = MetaData->AnimationBlueprint.Get();
								OnLoad();
								UE_LOG(LogTemp, Log, TEXT("Successfully loaded AnimInstance: %s"), *MetaData->AnimationBlueprint.Get()->GetName());
							}
							else
							{
								UE_LOG(LogTemp, Warning, TEXT("Failed to load AnimInstance for path: %s"), *MetaData->AnimationBlueprint.ToSoftObjectPath().ToString());
							}
						}));
			}
			else
			{
				UE_LOG(LogTemp, Warning, TEXT("Animation Blueprint is null or invalid for %s"), *MetaData->EnemyTag.ToString());
			}
		}
	}
};

UCLASS()
class VAMPIRESURVIVORCLONE_API AEnemySpawner : public AActor
{
	GENERATED_BODY()

private:
	// // This should be outside of this class, but kept here for simplicity for now.
	//UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Enemies", meta = (AllowPrivateAccess = "true"))
	TMap<FGameplayTag, TObjectPtr<UEnemyData>> EnemiesData;

	// UPROPERTY()
	// TArray<FEnemySpawnInfo> EnemiesSpawnInfo;
	
	FString CurrentLevelName;

	TWeakObjectPtr<APlayerCharacter> PlayerCharacter;
	
	FVector PlayerCharacterScale;

protected:
	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UDataTable> EnemiesInfo;
	
public:	
	// Sets default values for this actor's properties
	AEnemySpawner();
	virtual ~AEnemySpawner() override;

	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	void ProcessDataTable(UDataTable* DataTable);
	void OnHeroPlayerLevelChanged(int32 NewLevel);
};
