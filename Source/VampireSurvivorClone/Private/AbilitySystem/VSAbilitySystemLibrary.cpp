// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/VSAbilitySystemLibrary.h"

#include "GameplayTagsManager.h"
#include "AbilitySystem/PlayerAttributeSet.h"
#include "AbilitySystem/VSAbilitySystemComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Player/PlayerCharacterController.h"
#include "Player/PlayerCharacterState.h"
#include "UI/HUD/VSHUD.h"
#include "UI/WidgetController/OverlayWidgetController.h"
#include "UI/WidgetController/VSCWidgetController.h"

bool UVSAbilitySystemLibrary::MakeWidgetControllerParams(const UObject* WorldContextObject,
                                                         FWidgetControllerParams& OutWidgetControllerParams, AVSHUD*& OutHUD)
{
	if (APlayerCharacterController* PlayerController = Cast<APlayerCharacterController>(UGameplayStatics::GetPlayerController(WorldContextObject,0)))
	{
		OutHUD = Cast<AVSHUD>(PlayerController->GetHUD());

		if (OutHUD)
		{
			APlayerCharacterState* PlayerState = PlayerController->GetPlayerState<APlayerCharacterState>();
			UVSAbilitySystemComponent* AbilitySystemComponent = Cast<UVSAbilitySystemComponent>(PlayerState->GetAbilitySystemComponent());
			UPlayerAttributeSet* AttributeSet = Cast<UPlayerAttributeSet>(PlayerState->GetAttributeSetComponent());

			OutWidgetControllerParams.PlayerController = PlayerController;
			OutWidgetControllerParams.AbilitySystemComponent = AbilitySystemComponent;
			OutWidgetControllerParams.PlayerState = PlayerState;
			OutWidgetControllerParams.AttributeSet = AttributeSet;

			return true;
		}
		
	}
	return false;
}

UOverlayWidgetController* UVSAbilitySystemLibrary::GetOverlayWidgetController(const UObject* WorldContextObject)
{
	FWidgetControllerParams WidgetControllerParams;
	AVSHUD* Hud = nullptr;
	if (MakeWidgetControllerParams(WorldContextObject, WidgetControllerParams, Hud))
	{
		return Hud->GetOverlayWidgetController(WidgetControllerParams);
	}
	return nullptr;
}

UPauseOverlayWidgetController* UVSAbilitySystemLibrary::GetPauseOverlayWidgetController(
	const UObject* WorldContextObject)
{
	FWidgetControllerParams WidgetControllerParams;
	AVSHUD* Hud = nullptr;
	if (MakeWidgetControllerParams(WorldContextObject, WidgetControllerParams, Hud))
	{
		return Hud->GetOverlayWidgetController(WidgetControllerParams)->GetPauseWidgetController(WidgetControllerParams);
	}
	return nullptr;
}

TArray<FGameplayTag> UVSAbilitySystemLibrary::GetAllGameplayTagsThatMatch(const FString& MatchString)
{	
	UGameplayTagsManager& Manager = UGameplayTagsManager::Get();
	TArray<FGameplayTag> Tags;
	FGameplayTagContainer Container;
	Manager.RequestAllGameplayTags(Container, false);
	Container.GetGameplayTagArray(Tags);

	TArray<FGameplayTag> ReturnTags;

	for (FGameplayTag Tag : Tags)
	{
		if (Tag.RequestDirectParent().ToString().Equals(MatchString,ESearchCase::IgnoreCase))
		{
			ReturnTags.Add(Tag);
		}
	}
	
	return ReturnTags;
}
