// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "VampireSurvivorCloneGameMode.generated.h"

#define ECC_LandChannel ECC_GameTraceChannel1
#define ECC_ProjectileChannel ECollisionChannel::ECC_GameTraceChannel2
#define ECC_EnemyChannel ECollisionChannel::ECC_GameTraceChannel3
#define ECC_PickupItemsChannel ECollisionChannel::ECC_GameTraceChannel4
#define ECC_PlayerCharacterChannel ECollisionChannel::ECC_GameTraceChannel5

/**
 * 
 */
UCLASS()
class VAMPIRESURVIVORCLONE_API AVampireSurvivorCloneGameMode : public AGameMode
{
	GENERATED_BODY()

public:
	AVampireSurvivorCloneGameMode();
	
};
