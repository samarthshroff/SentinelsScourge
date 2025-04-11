#include "VampireSurvivorGameplayTags.h"

namespace VampireSurvivorGameplayTags
{
	// Enemy Tags
	UE_DEFINE_GAMEPLAY_TAG(Enemy_Beholder, "Enemy.Beholder");
	UE_DEFINE_GAMEPLAY_TAG(Enemy_Cactus, "Enemy.Cactus");
	UE_DEFINE_GAMEPLAY_TAG(Enemy_ChestMonster,"Enemy.ChestMonster");
	UE_DEFINE_GAMEPLAY_TAG(Enemy_Mushroom, "Enemy.Mushroom");
	UE_DEFINE_GAMEPLAY_TAG(Enemy_Slime, "Enemy.Slime");
	UE_DEFINE_GAMEPLAY_TAG(Enemy_SwarmFish,"Enemy.SwarmFish");
	UE_DEFINE_GAMEPLAY_TAG(Enemy_SwarmInsect, "Enemy.SwarmInsect");
	UE_DEFINE_GAMEPLAY_TAG(Enemy_Turtle, "Enemy.Turtle");
	
	// Player Character (Avatar) tags
	UE_DEFINE_GAMEPLAY_TAG(Hero_Antonio, "Hero.Antonio");

	FGameplayTag FindTagByString(const FString& TagString, bool bMatchPartialString)
	{
		const UGameplayTagsManager& Manager = UGameplayTagsManager::Get();
		FGameplayTag Tag = Manager.RequestGameplayTag(FName(*TagString), false);

		if (!Tag.IsValid() && bMatchPartialString)
		{
			FGameplayTagContainer AllTags;
			Manager.RequestAllGameplayTags(AllTags, true);

			for (const FGameplayTag& TempTag : AllTags)
			{
				if (TempTag.ToString().Contains(TagString))
				{
					UE_LOG(LogTemp, Display, TEXT("Could not find exact tag [%s] but found a partial match on tag [%s]"), *TagString, *TempTag.ToString());
					Tag = TempTag;
					break;
				}
			}
		}
		return Tag;
	}
}
