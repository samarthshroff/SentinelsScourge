// Fill out your copyright notice in the Description page of Project Settings.


#include "VampireSurvivorCloneGameMode.h"

#include "PlayerCharacter/PlayerCharacter.h"
#include "PlayerCharacter/PlayerCharacterController.h"

AVampireSurvivorCloneGameMode::AVampireSurvivorCloneGameMode()
{
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnFinder(TEXT("/Game/Blueprints/BP_PlayerCharacter"));
	DefaultPawnClass = PlayerPawnFinder.Class;
	PlayerControllerClass = APlayerCharacterController::StaticClass();
}
