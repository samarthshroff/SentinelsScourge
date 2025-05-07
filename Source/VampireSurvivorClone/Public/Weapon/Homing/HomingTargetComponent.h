// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Components/ActorComponent.h"
#include "Components/SphereComponent.h"
#include "HomingTargetComponent.generated.h"

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class VAMPIRESURVIVORCLONE_API UHomingTargetComponent : public USphereComponent
{
	GENERATED_BODY()

	UPROPERTY()
	TSet<TObjectPtr<AActor>> Enemies;

	float DefaultTargetingRadius;

	UPROPERTY()
	FGameplayTag WeaponTag;

	UPROPERTY()
	TObjectPtr<UCurveTable> TargetingRadiusCurveTable;

public:
	// Sets default values for this component's properties
	UHomingTargetComponent();

	void Initialize(const FGameplayTag& InTag);

	FVector GetClosestActorLocation() const;

protected:
	UFUNCTION()
	void OnTargetingSphereOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
							  const FHitResult& SweepResult);

private:
	void UpdateTargetingSphereRadius();
};
