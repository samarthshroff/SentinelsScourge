// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "VampireSurvivorEffectActor.generated.h"

class UGameplayEffect;
/*
 * Effector Actor class for pick-ups and other actors that influence player stats during ingame.
 * Parent to the BPs for each Effector.
 */
UCLASS()
class VAMPIRESURVIVORCLONE_API AVampireSurvivorEffectActor : public AActor
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category=Component, Meta=(AllowPrivateAccess=true))
	TObjectPtr<USceneComponent> SceneRoot;
public:	
	// Sets default values for this actor's properties
	AVampireSurvivorEffectActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Applied Gameplay Effect")
	TSubclassOf<UGameplayEffect> InstantGameplayEffectClass;

	UFUNCTION(BlueprintCallable)
	void ApplyGamePlayEffectToTarget(const AActor* TargetActor, const TSubclassOf<UGameplayEffect>& InGameplayEffectClass, bool ShouldDestroySelf);
};
