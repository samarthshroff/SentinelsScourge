// Fill out your copyright notice in the Description page of Project Settings.


#include "VampireSurvivorCloneGameMode.h"

#include "../Public/Player/PlayerCharacter.h"
#include "../Public/Player/PlayerCharacterController.h"
#include "Player/PlayerCharacterState.h"

AVampireSurvivorCloneGameMode::AVampireSurvivorCloneGameMode()
{
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnFinder(TEXT("/Game/Blueprints/Actor/BP_PlayerCharacter"));
	DefaultPawnClass = PlayerPawnFinder.Class;
	PlayerControllerClass = APlayerCharacterController::StaticClass();

	static ConstructorHelpers::FClassFinder<APlayerState> PlayerStateFinder(TEXT("/Game/Blueprints/BP_PlayerCharacterState"));
	if (PlayerStateFinder.Class != nullptr)
	{
		PlayerStateClass = PlayerStateFinder.Class;	
	}	
}
