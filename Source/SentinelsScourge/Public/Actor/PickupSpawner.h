// Copyright (c) Samarth Shroff. All Rights Reserved.
// This work is protected under applicable copyright laws in perpetuity.
// Licensed under the CC BY-NC-ND 4.0 License. See LICENSE file for details.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PickupSpawner.generated.h"

class APickupItem;

UENUM(BlueprintType)
enum class EXPPickupType : uint8
{
	Blue UMETA(DisplayName = "Blue"),
	Green UMETA(DisplayName = "Green"),
	Red UMETA(DisplayName = "Red")
};

UCLASS()
class SENTINELSSCOURGE_API APickupSpawner : public AActor
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "XP Pickups")
	TMap<EXPPickupType, TSubclassOf<APickupItem>> XPPickups;

public:
	// Sets default values for this actor's properties
	APickupSpawner();

	void SpawnPickup(const FVector &Location, const float XP);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	UFUNCTION()
	void OnCharacterDestroyed(const AActor *InActor);
};
