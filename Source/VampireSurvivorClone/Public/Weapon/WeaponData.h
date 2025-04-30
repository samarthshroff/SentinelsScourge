#pragma once

#include "GameplayAbilitySpecHandle.h"
#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "GameplayTagContainer.h"
#include "WeaponData.generated.h"

class UWeaponAttributeSet;
class UVSGameplayAbility;

USTRUCT(BlueprintType)
struct VAMPIRESURVIVORCLONE_API FWeaponMetaData //: public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FGameplayTag Category;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FGameplayTag Name;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSoftClassPtr<UVSGameplayAbility> AbilityClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSoftClassPtr<UWeaponAttributeSet> AttributeSet;
	
	// UPROPERTY(EditAnywhere, BlueprintReadWrite)
	// TSoftClassPtr<UVSGameplayAbility> AbilityClass;
	
	// UPROPERTY(EditAnywhere, BlueprintReadWrite)
	// FAssetVariant Asset;
	//
	// UPROPERTY(EditAnywhere, BlueprintReadWrite)
	// TSoftObjectPtr<UStaticMesh> UIStaticMesh;
	
// protected:
// 	UPROPERTY()
// 	FGameplayAbilitySpecHandle AbilitySpecHandle;
//
// 	UPROPERTY()
// 	TObjectPtr<UWeaponAttributeSet> AttributeSet;
	
public:	
	FWeaponMetaData() = default;
		
	FWeaponMetaData(const FWeaponMetaData& Other):
	Category(Other.Category),
	Name(Other.Name),
	AbilityClass(Other.AbilityClass),
	AttributeSet(Other.AttributeSet)
	// AbilitySpecHandle(Other.AbilitySpecHandle),
	// AttributeSet(Other.AttributeSet)
	//Asset(Other.Asset)
	{
	}
	
	FWeaponMetaData& operator=(const FWeaponMetaData& Other)
	{
		if (this != &Other)
		{
			Name = Other.Name;
			Category = Other.Category;
			AbilityClass = Other.AbilityClass;
			AttributeSet = Other.AttributeSet;
			
			// AbilitySpecHandle = Other.AbilitySpecHandle;
			// AttributeSet = Other.AttributeSet;
			//Asset = Other.Asset;
		}
		return *this;
	}
	
	FWeaponMetaData(FWeaponMetaData&& Other) noexcept:
	Category(MoveTemp(Other.Category)),
	Name(MoveTemp(Other.Name)),
	AbilityClass(MoveTemp(Other.AbilityClass)),
	AttributeSet(MoveTemp(Other.AttributeSet))
	// AbilitySpecHandle(MoveTemp(Other.AbilitySpecHandle)),
	// AttributeSet(MoveTemp(Other.AttributeSet))
	//Asset(MoveTemp(Other.Asset))
	{
	}
	
	FWeaponMetaData& operator=(FWeaponMetaData&& Other) noexcept
	{
		if (this != &Other)
		{
			Name = MoveTemp(Other.Name);
			Category = MoveTemp(Other.Category);
			AbilityClass = MoveTemp(Other.AbilityClass);
			AttributeSet = MoveTemp(Other.AttributeSet);
			
			// AbilitySpecHandle = MoveTemp(Other.AbilitySpecHandle);
			// AttributeSet = MoveTemp(Other.AttributeSet);
			//Asset = MoveTemp(Other.Asset);
		}
		return *this;
	}
};

UCLASS()
class VAMPIRESURVIVORCLONE_API UWeaponData : public UDataAsset
{
	GENERATED_BODY()
public:
	TOptional<FWeaponMetaData> FindAbilityDataForTag(const FGameplayTag& WeaponTag, bool bLogNotFound = true);

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TArray<FWeaponMetaData> WeaponsInfo;	
};
