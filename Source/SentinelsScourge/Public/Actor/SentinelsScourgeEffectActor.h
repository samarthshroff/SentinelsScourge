// Copyright (c) Samarth Shroff. All Rights Reserved.
// This work is protected under applicable copyright laws in perpetuity.
// Licensed under the CC BY-NC-ND 4.0 License. See LICENSE file for details.

#pragma once

#include "CoreMinimal.h"
#include "ActiveGameplayEffectHandle.h"
#include "GameplayTagContainer.h"
#include "PickupSpawner.h"
#include "GameFramework/Actor.h"
#include "SentinelsScourgeEffectActor.generated.h"

struct FGameplayEffectContext;
struct FGameplayEffectContextHandle;
class UAbilitySystemComponent;
class UGameplayEffect;

UENUM(BlueprintType)
enum class EGameplayEffectApplicationPolicy : uint8
{
	DoNotApply,
	ApplyOnBeginOverlap,
	ApplyOnEndOverlap,
};

UENUM(BlueprintType)
enum class EGameplayEffectRemovalPolicy : uint8
{
	RemoveOnEndOverlap,
	DoNotRemove
};

/*
 * Effector Actor class for pick-ups and other actors that influence player stats during ingame.
 * Parent to the BPs for each Effector.
 */
UCLASS()
class SENTINELSSCOURGE_API ASentinelsScourgeEffectActor : public AActor
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Component, Meta = (AllowPrivateAccess = true))
	TObjectPtr<USceneComponent> SceneRoot;

protected:
	UPROPERTY()
	TMap<FActiveGameplayEffectHandle, UAbilitySystemComponent *> InfiniteActiveGEHandles;

	// This can be 3 TMaps one for each policy - instant, has duration and infinite.
	// For simplicity and targeted use I am going to have only one TMap for now. May change it if required.
	UPROPERTY()
	TMap<FGameplayTag, float> SetByCallerValues;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Applied GameplayEffect")
	bool bShouldDestroyOnRemoval;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Applied GameplayEffect")
	TSubclassOf<UGameplayEffect> InstantGameplayEffectClass;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Applied GameplayEffect")
	EGameplayEffectApplicationPolicy InstantGEApplicationPolicy = EGameplayEffectApplicationPolicy::DoNotApply;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Applied GameplayEffect")
	TSubclassOf<UGameplayEffect> HasDurationGameplayEffectClass;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Applied GameplayEffect")
	EGameplayEffectApplicationPolicy HasDurationGEApplicationPolicy = EGameplayEffectApplicationPolicy::DoNotApply;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Applied GameplayEffect")
	TSubclassOf<UGameplayEffect> InfiniteGameplayEffectClass;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Applied GameplayEffect")
	EGameplayEffectApplicationPolicy InfiniteGEApplicationPolicy = EGameplayEffectApplicationPolicy::DoNotApply;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Applied GameplayEffect")
	EGameplayEffectRemovalPolicy InfiniteGERemovalPolicy = EGameplayEffectRemovalPolicy::RemoveOnEndOverlap;

public:
	// Sets default values for this actor's properties
	ASentinelsScourgeEffectActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable, BlueprintPure)
	virtual FGameplayEffectContextHandle MakeEffectContext(const UAbilitySystemComponent *AbilitySystemComponent);

	UFUNCTION(BlueprintCallable)
	void OnBeginOverlap(AActor *TargetActor, const float Level = 1.0f);

	UFUNCTION(BlueprintCallable)
	void OnEndOverlap(AActor *TargetActor, const float Level = 1.0f);

	UFUNCTION(BlueprintCallable)
	void ApplyGamePlayEffectToTarget(const AActor *InTargetActor, const TSubclassOf<UGameplayEffect> &InGameplayEffectClass, const float Level);
};
