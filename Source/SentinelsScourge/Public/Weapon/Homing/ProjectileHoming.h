// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Actor/SentinelsScourgeEffectActor.h"
#include "GameFramework/Actor.h"
#include "ProjectileHoming.generated.h"

class UWeaponAttributeSet;
class UProjectileMovementComponent;
class USphereComponent;

UCLASS(Blueprintable, BlueprintType)
class SENTINELSSCOURGE_API AProjectileHoming : public ASentinelsScourgeEffectActor
{
	GENERATED_BODY()

private:
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<USphereComponent> Sphere;

	// Actor to lock on to and follow
	UPROPERTY()
	TObjectPtr<const AActor> HomingTargetActor;

	// The hero actor
	UPROPERTY()
	TObjectPtr<AActor> AvatarActor;

	bool bIsBlockedByWalls = false;

	float Speed;
	float Pierce;
	float Damage;
	float PierceCount;
	float Area;
	float Level;
	float Knockback;

public:
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UProjectileMovementComponent> ProjectileMovement;

	UPROPERTY(EditDefaultsOnly)
	float LifeSpan = 10.0f;

protected:
	UFUNCTION()
	void OnSphereOverlap(UPrimitiveComponent *OverlappedComponent, AActor *OtherActor, UPrimitiveComponent *OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult &SweepResult);

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void Tick(float DeltaSeconds) override;

	virtual FGameplayEffectContextHandle MakeEffectContext(const UAbilitySystemComponent *AbilitySystemComponent) override;

public:
	// Sets default values for this actor's properties
	AProjectileHoming();

	void Initialize(const bool InbBlockedByWalls, const float InSpeed, const float InPierce, const float InDamage, const float InArea, const float InLevel,
					const float InKnockback, const TObjectPtr<const AActor> &InHomingTargetActor, const TObjectPtr<AActor> &InAvatarActor);
};
