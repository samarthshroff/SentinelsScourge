// Copyright (c) Samarth Shroff. All Rights Reserved.
// This work is protected under applicable copyright laws in perpetuity.
// Licensed under the CC BY-NC-ND 4.0 License. See LICENSE file for details.

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
