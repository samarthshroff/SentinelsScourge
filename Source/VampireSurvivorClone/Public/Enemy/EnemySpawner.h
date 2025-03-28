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

DECLARE_DELEGATE_TwoParams(FOnAssetsLoaded, const FGameplayTag&, double);

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

	bool IsLoaded;

	FOnAssetsLoaded OnAssetsLoaded;

	void OnLoad()
	{
		if (SkeletalMesh != nullptr && AnimInstance != nullptr)
		{
			UE_LOG(LogTemp, Log, TEXT("Enemy Data loaded for %s"), *(MetaData->EnemyTag.ToString()));
			IsLoaded = true;
			OnAssetsLoaded.ExecuteIfBound(MetaData->EnemyTag, MetaData->SpawnIntervalInSeconds);			
		}
	}

	void Initialize(FEnemyMetaData* Data)
	{
		MetaData = MakeUnique<FEnemyMetaData>(*Data);

		FStreamableManager& Manager = UAssetManager::GetStreamableManager();

		if (MetaData->Mesh.IsValid())
		{
			UE_LOG(LogTemp, Log, TEXT("Mesh already valid: %s"), *MetaData->Mesh.ToSoftObjectPath().ToString());
			SkeletalMesh = MetaData->Mesh.Get();
			OnLoad();
		}
		else
		{
			TSoftObjectPtr<USkeletalMesh> Mesh = MetaData->Mesh;
			UE_LOG(LogTemp, Log, TEXT("Mesh Path: %s"), *Mesh.ToSoftObjectPath().ToString());
			Manager.RequestAsyncLoad(Mesh.ToSoftObjectPath(),
				FStreamableDelegate::CreateLambda([&Mesh, this]()
				{
					if (Mesh.IsValid())
					{
						this->SkeletalMesh = Mesh.Get();
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
				TSoftClassPtr<UAnimInstance> Anim = MetaData->AnimationBlueprint;
				UE_LOG(LogTemp, Log, TEXT("Anim Path: %s"), *Anim.ToSoftObjectPath().ToString());
				Manager.RequestAsyncLoad(Anim.ToSoftObjectPath(),
						FStreamableDelegate::CreateWeakLambda(this, [this, Anim]()
						{
							if (Anim.IsValid())
							{
								this->AnimInstance = Anim.Get();
								OnLoad();
								UE_LOG(LogTemp, Log, TEXT("Successfully loaded AnimInstance: %s"), *Anim.Get()->GetName());
							}
							else
							{
								UE_LOG(LogTemp, Warning, TEXT("Failed to load AnimInstance for path: %s"), *Anim.ToSoftObjectPath().ToString());
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
	TMap<FGameplayTag, TObjectPtr<UEnemyData>> EnemiesDataForCurrentLevel;
	TMap<FGameplayTag, TTuple<double, double>> StartSeconds;

	FString CurrentLevelName;

	TWeakObjectPtr<APlayerCharacter> PlayerCharacter;
	
	FVector PlayerCharacterScale;
	
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
};
