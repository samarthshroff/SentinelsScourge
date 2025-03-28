// Fill out your copyright notice in the Description page of Project Settings.


#include "VampireSurvivorCloneGameMode.h"

#include "../Public/Player/PlayerCharacter.h"
#include "../Public/Player/PlayerCharacterController.h"
#include "Player/VampireSurvivorPlayerState.h"

AVampireSurvivorCloneGameMode::AVampireSurvivorCloneGameMode()
{
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnFinder(TEXT("/Game/Blueprints/BP_PlayerCharacter"));
	DefaultPawnClass = PlayerPawnFinder.Class;
	PlayerControllerClass = APlayerCharacterController::StaticClass();
	PlayerStateClass = AVampireSurvivorPlayerState::StaticClass();
}
