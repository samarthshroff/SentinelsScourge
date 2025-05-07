#include "Weapon/WeaponData.h"

TOptional<const FWeaponMetaData> UWeaponData::FindAbilityDataForTag(const FGameplayTag& WeaponTag, bool bLogNotFound)
{
	for (FWeaponMetaData& WeaponData : WeaponsInfo)
	{
		if (WeaponData.Name.MatchesTagExact(WeaponTag))
		{
			return WeaponData;
		}
	}

	if (bLogNotFound)
	{
		UE_LOG(LogTemp, Error, TEXT("Can't find Data for Weapon => %s in WeaponsInfo => %s."), *WeaponTag.ToString(),*GetNameSafe(this));
	}

	return NullOpt;
}
