#pragma once

UENUM(BlueprintType)
enum class UEnemyStates : uint8
{
	Idle        UMETA(DisplayName = "Idle"),
	//Spawning    UMETA(DisplayName = "Spawning"), May not be there as an enemy is already spawned by the time AI possesses it.
	Chasing     UMETA(DisplayName = "Chasing"),
	Attacking   UMETA(DisplayName = "Attacking"),
	Dying       UMETA(DisplayName = "Dying"),
	Dead        UMETA(DisplayName = "Dead")
};
