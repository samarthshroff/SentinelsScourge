#pragma once

#include "GameplayAbilitySpecHandle.h"
#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "GameplayTagContainer.h"
#include "WeaponData.generated.h"

class UGameplayEffect;
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

	// This Gameplay Effects that has the initial default values for weapon attribute
	// will also have the next attribute to apply in the components section.
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSoftClassPtr<UGameplayEffect> DefaultAttributes;	

public:	
	FWeaponMetaData() = default;
		
	FWeaponMetaData(const FWeaponMetaData& Other) = default;
	
	FWeaponMetaData& operator=(const FWeaponMetaData& Other) = default;
	
	FWeaponMetaData(FWeaponMetaData&& Other) noexcept = default;
	
	FWeaponMetaData& operator=(FWeaponMetaData&& Other) noexcept = default;
};

UCLASS()
class VAMPIRESURVIVORCLONE_API UWeaponData : public UDataAsset
{
	GENERATED_BODY()
public:
	TOptional<const FWeaponMetaData> FindAbilityDataForTag(const FGameplayTag& WeaponTag, bool bLogNotFound = true);

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TArray<FWeaponMetaData> WeaponsInfo;	
};
