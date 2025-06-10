// Fill out your copyright notice in the Description page of Project Settings.

#include "SentinelsScourgeGameMode.h"

#include "../Public/Player/PlayerCharacter.h"
#include "../Public/Player/PlayerCharacterController.h"
#include "Player/PlayerCharacterState.h"
#include "UI/HUD/SSHUD.h"

ASentinelsScourgeGameMode::ASentinelsScourgeGameMode()
{
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnFinder(TEXT("/Game/Blueprints/Actor/BP_PlayerCharacter"));
	DefaultPawnClass = PlayerPawnFinder.Class;
	PlayerControllerClass = APlayerCharacterController::StaticClass();

	static ConstructorHelpers::FClassFinder<APlayerState> PlayerStateFinder(TEXT("/Game/Blueprints/BP_PlayerCharacterState"));
	if (PlayerStateFinder.Class != nullptr)
	{
		PlayerStateClass = PlayerStateFinder.Class;
	}

	static ConstructorHelpers::FClassFinder<AHUD> GameHUD(TEXT("/Game/Blueprints/UI/HUD/BP_HUD"));
	if (GameHUD.Class != nullptr)
	{
		HUDClass = GameHUD.Class;
	}
}
