#include "VampireSurvivorGameplayTags.h"

namespace VampireSurvivorGameplayTags
{
	// Player Attributes Tags
	UE_DEFINE_GAMEPLAY_TAG(Player_Attributes_Health,"Player.Attributes.Health");
	UE_DEFINE_GAMEPLAY_TAG(Player_Attributes_MaxHealth,"Player.Attributes.MaxHealth");
	UE_DEFINE_GAMEPLAY_TAG(Player_Attributes_Recovery,"Player.Attributes.Recovery");
	UE_DEFINE_GAMEPLAY_TAG(Player_Attributes_Armor,"Player.Attributes.Armor");
	UE_DEFINE_GAMEPLAY_TAG(Player_Attributes_MoveSpeed,"Player.Attributes.MoveSpeed");
	UE_DEFINE_GAMEPLAY_TAG(Player_Attributes_Might,"Player.Attributes.Might");
	UE_DEFINE_GAMEPLAY_TAG(Player_Attributes_Area,"Player.Attributes.Area");
	UE_DEFINE_GAMEPLAY_TAG(Player_Attributes_Speed,"Player.Attributes.Speed");
	UE_DEFINE_GAMEPLAY_TAG(Player_Attributes_Duration,"Player.Attributes.Duration");
	UE_DEFINE_GAMEPLAY_TAG(Player_Attributes_Amount,"Player.Attributes.Amount");
	UE_DEFINE_GAMEPLAY_TAG(Player_Attributes_Cooldown,"Player.Attributes.Cooldown");
	UE_DEFINE_GAMEPLAY_TAG(Player_Attributes_Luck,"Player.Attributes.Luck");
	UE_DEFINE_GAMEPLAY_TAG(Player_Attributes_Growth,"Player.Attributes.Growth");
	UE_DEFINE_GAMEPLAY_TAG(Player_Attributes_Greed,"Player.Attributes.Greed");
	UE_DEFINE_GAMEPLAY_TAG(Player_Attributes_Curse,"Player.Attributes.Curse");
	UE_DEFINE_GAMEPLAY_TAG(Player_Attributes_Magnet,"Player.Attributes.Magnet");
	UE_DEFINE_GAMEPLAY_TAG(Player_Attributes_Revival,"Player.Attributes.Revival");
	UE_DEFINE_GAMEPLAY_TAG(Player_Attributes_Reroll,"Player.Attributes.Reroll");
	UE_DEFINE_GAMEPLAY_TAG(Player_Attributes_Skip,"Player.Attributes.Skip");
	UE_DEFINE_GAMEPLAY_TAG(Player_Attributes_Banish,"Player.Attributes.Banish");
	UE_DEFINE_GAMEPLAY_TAG(Player_Attributes_Charm,"Player.Attributes.Charm");
	UE_DEFINE_GAMEPLAY_TAG(Player_Attributes_Defang,"Player.Attributes.Defang");
	UE_DEFINE_GAMEPLAY_TAG(Player_Attributes_Seal,"Player.Attributes.Seal");
	UE_DEFINE_GAMEPLAY_TAG(Player_Attributes_Level,"Player.Attributes.Level");
	UE_DEFINE_GAMEPLAY_TAG(Player_Attributes_XP,"Player.Attributes.XP");
	UE_DEFINE_GAMEPLAY_TAG(Player_Attributes_MaxXP,"Player.Attributes.MaxXP");

	
	// Enemy Tags
	UE_DEFINE_GAMEPLAY_TAG(Enemy_Root, "Enemy.Root");
	UE_DEFINE_GAMEPLAY_TAG(Enemy_Beholder, "Enemy.Beholder");
	UE_DEFINE_GAMEPLAY_TAG(Enemy_Cactus, "Enemy.Cactus");
	UE_DEFINE_GAMEPLAY_TAG(Enemy_ChestMonster,"Enemy.ChestMonster");
	UE_DEFINE_GAMEPLAY_TAG(Enemy_Mushroom, "Enemy.Mushroom");
	UE_DEFINE_GAMEPLAY_TAG(Enemy_Slime, "Enemy.Slime");
	UE_DEFINE_GAMEPLAY_TAG(Enemy_SwarmFish,"Enemy.SwarmFish");
	UE_DEFINE_GAMEPLAY_TAG(Enemy_SwarmInsect, "Enemy.SwarmInsect");
	UE_DEFINE_GAMEPLAY_TAG(Enemy_Turtle, "Enemy.Turtle");
	
	// Player Character (Avatar) tags
	UE_DEFINE_GAMEPLAY_TAG(Hero_Root, "Hero");
	UE_DEFINE_GAMEPLAY_TAG(Hero_Antonio, "Hero.Antonio");

	// Weapons
	UE_DEFINE_GAMEPLAY_TAG(Weapon_Hero_MagicWand,"Weapon.Hero.MagicWand");
	UE_DEFINE_GAMEPLAY_TAG(Weapon_Hero_Knife, "Weapon.Hero.Knife");
	UE_DEFINE_GAMEPLAY_TAG(Weapon_Hero_Axe, "Weapon.Hero.Axe");

	// Weapon Categories
	UE_DEFINE_GAMEPLAY_TAG(Weapon_Category_Projectile_Direct, "Weapon.Category.Projectile.Direct");
	UE_DEFINE_GAMEPLAY_TAG(Weapon_Category_Projectile_Orbiting, "Weapon.Category.Projectile.Orbiting");
	UE_DEFINE_GAMEPLAY_TAG(Weapon_Category_Projectile_Bouncing, "Weapon.Category.Projectile.Bouncing");
	UE_DEFINE_GAMEPLAY_TAG(Weapon_Category_Melee_ConstantArea, "Weapon.Category.Melee.ConstantArea");
	UE_DEFINE_GAMEPLAY_TAG(Weapon_Category_Melee_PulsingArea, "Weapon.Category.Melee.PulsingArea");
	UE_DEFINE_GAMEPLAY_TAG(Weapon_Category_Unique_Targeted, "Weapon.Category.Unique.Targeted");
	UE_DEFINE_GAMEPLAY_TAG(Weapon_Category_Unique_ScreenClearing, "Weapon.Category.Unique.ScreenClearing");
	UE_DEFINE_GAMEPLAY_TAG(Weapon_Category_Unique_Transformative, "Weapon.Category.Unique.Transformative");
	UE_DEFINE_GAMEPLAY_TAG(Weapon_Category_Unique_Retaliatory, "Weapon.Category.Unique.Retaliatory");
	UE_DEFINE_GAMEPLAY_TAG(Weapon_Category_Unique_Arcing, "Weapon.Category.Unique.Arcing");

	// Weapon Cooldown
	UE_DEFINE_GAMEPLAY_TAG(Weapon_Cooldown,"Weapon.Cooldown");
	UE_DEFINE_GAMEPLAY_TAG(Weapon_Cooldown_MagicWand,"Weapon.Cooldown.MagicWand");
	UE_DEFINE_GAMEPLAY_TAG(Weapon_Cooldown_Knife, "Weapon.Cooldown.Knife");
	UE_DEFINE_GAMEPLAY_TAG(Weapon_Cooldown_Axe, "Weapon.Cooldown.Axe");

	// Effectors
	UE_DEFINE_GAMEPLAY_TAG(Effect_Modifier_Damage, "Effect.Modifier.Damage");
	UE_DEFINE_GAMEPLAY_TAG(Effect_Modifier_MoveSpeed,"Effect.Modifier.MoveSpeed");
	UE_DEFINE_GAMEPLAY_TAG(Effect_Modifier_Knockback,"Effect.Modifier.Knockback");
	UE_DEFINE_GAMEPLAY_TAG(Effect_Modifier_XP,"Effect.Modifier.XP");
	
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
