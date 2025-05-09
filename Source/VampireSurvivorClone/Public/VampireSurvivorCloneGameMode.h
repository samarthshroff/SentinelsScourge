// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "VampireSurvivorCloneGameMode.generated.h"

#define ECC_LandChannel ECC_GameTraceChannel1
#define ECC_ProjectileChannel ECollisionChannel::ECC_GameTraceChannel2

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
