#pragma once
#include "GameplayTagContainer.h"
#include "NiagaraSystem.h"
#include "WeaponsMetaData.generated.h"

USTRUCT(BlueprintType)
struct VAMPIRESURVIVORCLONE_API FWeaponsMetaData : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FGameplayTag Category;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FGameplayTag Name;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSoftClassPtr<UNiagaraSystem> NiagaraSystemClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSoftObjectPtr<UStaticMesh> StaticMesh;
	
	FWeaponsMetaData() = default;
		
	FWeaponsMetaData(const FWeaponsMetaData& Other)
	{
		Name = Other.Name;
		Category = Other.Category;
		NiagaraSystemClass = Other.NiagaraSystemClass;
		StaticMesh = Other.StaticMesh;
	}
	
	FWeaponsMetaData& operator=(const FWeaponsMetaData& Other)
	{
		if (this != &Other)
		{
			Name = Other.Name;
			Category = Other.Category;
			NiagaraSystemClass = Other.NiagaraSystemClass;
			StaticMesh = Other.StaticMesh;
		}
		return *this;
	}
	
	FWeaponsMetaData(FWeaponsMetaData&& Other) noexcept
	{
		Name = Other.Name;
		Category = Other.Category;
		NiagaraSystemClass = MoveTemp(Other.NiagaraSystemClass);
		StaticMesh = MoveTemp(Other.StaticMesh);
	}
	
	FWeaponsMetaData& operator=(FWeaponsMetaData&& Other) noexcept
	{
		if (this != &Other)
		{
			Name = Other.Name;
			Category = Other.Category;
			NiagaraSystemClass = MoveTemp(Other.NiagaraSystemClass);
			StaticMesh = MoveTemp(Other.StaticMesh);
		}
		return *this;
	}
};
