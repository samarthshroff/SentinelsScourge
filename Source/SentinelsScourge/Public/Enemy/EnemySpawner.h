// Copyright (c) Samarth Shroff. All Rights Reserved.
// This work is protected under applicable copyright laws in perpetuity.
// Licensed under the CC BY-NC-ND 4.0 License. See LICENSE file for details.

#pragma once

#include "CoreMinimal.h"
#include "EnemyMetaData.h"
#include "GameplayTagContainer.h"

#include "Engine/AssetManager.h"
#include "Engine/StreamableManager.h"
#include "GameFramework/Actor.h"
#include "EnemySpawner.generated.h"

class AEnemyCharacterBase;
class APlayerCharacter;

DECLARE_DELEGATE_TwoParams(FAssetsLoadedDelegate, const FGameplayTag &, double);

UCLASS()
class UEnemyData : public UObject
{
	GENERATED_BODY()
public:
	UPROPERTY()
	TObjectPtr<USkeletalMesh> SkeletalMesh;

	UPROPERTY()
	TObjectPtr<UClass> AnimInstance;

	UPROPERTY()
	TObjectPtr<UAnimMontage> AnimMontageDie;

	TUniquePtr<FEnemyMetaData> MetaData;

	UPROPERTY()
	TSubclassOf<UGameplayEffect> DefaultAttributeClass;

	bool bIsLoaded;

	FAssetsLoadedDelegate OnAssetsLoaded;

	double StartTimeInSeconds;

	void OnLoad()
	{
		if (SkeletalMesh != nullptr && AnimInstance != nullptr && AnimMontageDie != nullptr)
		{
			// UE_LOG(LogTemp, Log, TEXT("Enemy Data loaded for %s"), *(MetaData->EnemyTag.ToString()));

			const int Index = FMath::RandRange(0, MetaData->DefaultAttributes.Num() - 1);
			DefaultAttributeClass = MetaData->DefaultAttributes[Index].LoadSynchronous();

			bIsLoaded = true;
			OnAssetsLoaded.ExecuteIfBound(MetaData->EnemyTag, MetaData->SpawnIntervalInSeconds);
		}
	}

	void Initialize()
	{
		FStreamableManager &Manager = UAssetManager::GetStreamableManager();

		if (MetaData->Mesh.IsValid())
		{
			// UE_LOG(LogTemp, Log, TEXT("Mesh already valid: %s"), *MetaData->Mesh.ToSoftObjectPath().ToString());
			SkeletalMesh = MetaData->Mesh.Get();
			OnLoad();
		}
		else
		{
			// UE_LOG(LogTemp, Log, TEXT("Mesh Path: %s"), *MetaData->Mesh.ToSoftObjectPath().ToString());
			Manager.RequestAsyncLoad(MetaData->Mesh.ToSoftObjectPath(),
									 FStreamableDelegate::CreateLambda([this]()
																	   {
					if (MetaData->Mesh.IsValid())
					{
						this->SkeletalMesh = MetaData->Mesh.Get();
						OnLoad();
					} }));
		}

		// Load Anim Instance
		if (MetaData->AnimationBlueprint.IsValid())
		{
			// UE_LOG(LogTemp, Log, TEXT("Anim already valid: %s"), *MetaData->AnimationBlueprint.ToSoftObjectPath().ToString());
			AnimInstance = MetaData->AnimationBlueprint.Get();
			OnLoad();
		}
		else
		{
			if (!MetaData->AnimationBlueprint.IsNull())
			{
				// UE_LOG(LogTemp, Log, TEXT("Anim Path: %s"), *MetaData->AnimationBlueprint.ToSoftObjectPath().ToString());
				Manager.RequestAsyncLoad(MetaData->AnimationBlueprint.ToSoftObjectPath(),
										 FStreamableDelegate::CreateWeakLambda(this, [this]()
																			   {
							if (MetaData->AnimationBlueprint.IsValid())
							{
								this->AnimInstance = MetaData->AnimationBlueprint.Get();
								OnLoad();
								//UE_LOG(LogTemp, Log, TEXT("Successfully loaded AnimInstance: %s"), *MetaData->AnimationBlueprint.Get()->GetName());
							}
							else
							{
								UE_LOG(LogTemp, Warning, TEXT("Failed to load AnimInstance for path: %s"), *MetaData->AnimationBlueprint.ToSoftObjectPath().ToString());
							} }));
			}
			else
			{
				UE_LOG(LogTemp, Warning, TEXT("Animation Blueprint is null or invalid for %s"), *MetaData->EnemyTag.ToString());
			}
		}

		// Load Die Anim Montage
		if (MetaData->AnimationMontageDie.IsValid())
		{
			// UE_LOG(LogTemp, Log, TEXT("Anim already valid: %s"), *MetaData->AnimationMontageDie.ToSoftObjectPath().ToString());
			AnimMontageDie = MetaData->AnimationMontageDie.Get();
			OnLoad();
		}
		else
		{
			if (!MetaData->AnimationMontageDie.IsNull())
			{
				// UE_LOG(LogTemp, Log, TEXT("Anim Path: %s"), *MetaData->AnimationMontageDie.ToSoftObjectPath().ToString());
				Manager.RequestAsyncLoad(MetaData->AnimationMontageDie.ToSoftObjectPath(),
										 FStreamableDelegate::CreateLambda([this]()
																		   {
							if (MetaData->AnimationMontageDie.IsValid())
							{
								this->AnimMontageDie = MetaData->AnimationMontageDie.Get();
								OnLoad();
								//UE_LOG(LogTemp, Log, TEXT("Successfully loaded AnimMontageDie: %s"), *MetaData->AnimationMontageDie.Get()->GetName());
							}
							else
							{
								UE_LOG(LogTemp, Warning, TEXT("Failed to load AnimMontageDie for path: %s"), *MetaData->AnimationMontageDie.ToSoftObjectPath().ToString());
							} }));
			}
			else
			{
				UE_LOG(LogTemp, Warning, TEXT("Animation Montage Die is null or invalid for %s"), *MetaData->EnemyTag.ToString());
			}
		}
	}
};

UCLASS()
class SENTINELSSCOURGE_API AEnemySpawner : public AActor
{
	GENERATED_BODY()

private:
	// // This should be outside of this class, but kept here for simplicity for now.
	// UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Enemies", meta = (AllowPrivateAccess = "true"))
	TMap<FGameplayTag, TObjectPtr<UEnemyData>> EnemiesData;

	// UPROPERTY()
	// TArray<FEnemySpawnInfo> EnemiesSpawnInfo;

	FString CurrentLevelName;

	TWeakObjectPtr<APlayerCharacter> PlayerCharacter;

	FVector PlayerCharacterScale;
	FVector PlayerCharacterMeshScale;

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
	void ProcessDataTable(UDataTable *DataTable);
	void OnHeroPlayerLevelChanged(const FOnAttributeChangeData &AttributeData);
	void InitializeEnemies(int32 HeroLevel);
};
