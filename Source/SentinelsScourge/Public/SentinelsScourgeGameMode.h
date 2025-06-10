// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "SentinelsScourgeGameMode.generated.h"

#define ECC_LandChannel ECC_GameTraceChannel1
#define ECC_ProjectileChannel ECollisionChannel::ECC_GameTraceChannel2
#define ECC_EnemyChannel ECollisionChannel::ECC_GameTraceChannel3
#define ECC_PickupItemsChannel ECollisionChannel::ECC_GameTraceChannel4
#define ECC_PlayerCharacterChannel ECollisionChannel::ECC_GameTraceChannel5

/**
 *
 */
UCLASS()
class SENTINELSSCOURGE_API ASentinelsScourgeGameMode : public AGameMode
{
	GENERATED_BODY()

public:
	ASentinelsScourgeGameMode();
};
