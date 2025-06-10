// Copyright (c) Samarth Shroff. All Rights Reserved.
// This work is protected under applicable copyright laws in perpetuity.
// Licensed under the CC BY-NC-ND 4.0 License. See LICENSE file for details.

#pragma once

UENUM(BlueprintType)
enum class UEnemyStates : uint8
{
	Idle        UMETA(DisplayName = "Idle"),
	//Spawning    UMETA(DisplayName = "Spawning"), May not be there as an enemy is already spawned by the time AI possesses it.
	Chasing     UMETA(DisplayName = "Chasing"),
	Attacking   UMETA(DisplayName = "Attacking"),
	Knockback   UMETA(DisplayName = "Knockback"),
	Dying       UMETA(DisplayName = "Dying"),
	Dead        UMETA(DisplayName = "Dead")
};
