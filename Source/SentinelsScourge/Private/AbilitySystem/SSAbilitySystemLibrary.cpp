// Fill out your copyright notice in the Description page of Project Settings.

#include "AbilitySystem/SSAbilitySystemLibrary.h"

#include "GameplayTagsManager.h"
#include "AbilitySystem/PlayerAttributeSet.h"
#include "AbilitySystem/HeroAbilitySystemComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Player/PlayerCharacterController.h"
#include "Player/PlayerCharacterState.h"
#include "UI/HUD/SSHUD.h"
#include "UI/WidgetController/OverlayWidgetController.h"
#include "UI/WidgetController/PauseOverlayWidgetController.h"
#include "UI/WidgetController/LevelUpOverlayWidgetController.h"
#include "UI/WidgetController/SSCWidgetController.h"

bool USSAbilitySystemLibrary::MakeWidgetControllerParams(const UObject *WorldContextObject,
														 FWidgetControllerParams &OutWidgetControllerParams, ASSHUD *&OutHUD)
{
	if (APlayerCharacterController *PlayerController = Cast<APlayerCharacterController>(UGameplayStatics::GetPlayerController(WorldContextObject, 0)))
	{
		OutHUD = Cast<ASSHUD>(PlayerController->GetHUD());

		if (OutHUD)
		{
			APlayerCharacterState *PlayerState = PlayerController->GetPlayerState<APlayerCharacterState>();
			UHeroAbilitySystemComponent *AbilitySystemComponent = Cast<UHeroAbilitySystemComponent>(PlayerState->GetAbilitySystemComponent());
			UPlayerAttributeSet *AttributeSet = Cast<UPlayerAttributeSet>(PlayerState->GetAttributeSetComponent());

			OutWidgetControllerParams.PlayerController = PlayerController;
			OutWidgetControllerParams.AbilitySystemComponent = AbilitySystemComponent;
			OutWidgetControllerParams.PlayerState = PlayerState;
			OutWidgetControllerParams.AttributeSet = AttributeSet;

			return true;
		}
	}
	return false;
}

UOverlayWidgetController *USSAbilitySystemLibrary::GetOverlayWidgetController(const UObject *WorldContextObject)
{
	FWidgetControllerParams WidgetControllerParams;
	ASSHUD *Hud = nullptr;
	if (MakeWidgetControllerParams(WorldContextObject, WidgetControllerParams, Hud))
	{
		return Hud->GetOverlayWidgetController(WidgetControllerParams);
	}
	return nullptr;
}

UPauseOverlayWidgetController *USSAbilitySystemLibrary::GetPauseOverlayWidgetController(
	const UObject *WorldContextObject)
{
	FWidgetControllerParams WidgetControllerParams;
	ASSHUD *Hud = nullptr;
	if (MakeWidgetControllerParams(WorldContextObject, WidgetControllerParams, Hud))
	{
		return Hud->GetOverlayWidgetController(WidgetControllerParams)->GetPauseWidgetController(WidgetControllerParams);
	}
	return nullptr;
}

UAttributesMenuWidgetController *USSAbilitySystemLibrary::GetAttributesMenuWidgetController(const UObject *WorldContextObject)
{
	FWidgetControllerParams WidgetControllerParams;
	ASSHUD *Hud = nullptr;
	UAttributesMenuWidgetController *AttributesMenuController = nullptr;

	if (MakeWidgetControllerParams(WorldContextObject, WidgetControllerParams, Hud))
	{
		TObjectPtr<UOverlayWidgetController> OverlayWidgetController = Hud->GetOverlayWidgetController(WidgetControllerParams);

		if (OverlayWidgetController->GetCurrentlyShowingMenu() == ECurrentlyShowingMenu::PauseMenu)
		{
			return OverlayWidgetController->GetPauseWidgetController(WidgetControllerParams)->GetAttributesMenuWidgetController(WidgetControllerParams);
		}
		else if (OverlayWidgetController->GetCurrentlyShowingMenu() == ECurrentlyShowingMenu::LevelUpMenu)
		{
			return OverlayWidgetController->GetLevelUpOverlayWidgetController(WidgetControllerParams)->GetAttributesMenuWidgetController(WidgetControllerParams);
		}
	}
	return nullptr;
}

TArray<FGameplayTag> USSAbilitySystemLibrary::GetAllGameplayTagsThatMatch(const FString &MatchString)
{
	UGameplayTagsManager &Manager = UGameplayTagsManager::Get();
	TArray<FGameplayTag> Tags;
	FGameplayTagContainer Container;
	Manager.RequestAllGameplayTags(Container, false);
	Container.GetGameplayTagArray(Tags);

	TArray<FGameplayTag> ReturnTags;

	for (FGameplayTag Tag : Tags)
	{
		if (Tag.RequestDirectParent().ToString().Equals(MatchString, ESearchCase::IgnoreCase))
		{
			ReturnTags.Add(Tag);
		}
	}

	return ReturnTags;
}
