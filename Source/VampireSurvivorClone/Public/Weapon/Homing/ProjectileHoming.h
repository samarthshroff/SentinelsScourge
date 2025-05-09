// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Actor/VampireSurvivorEffectActor.h"
#include "GameFramework/Actor.h"
#include "ProjectileHoming.generated.h"

class UWeaponAttributeSet;
class UProjectileMovementComponent;
class USphereComponent;

UCLASS(Blueprintable, BlueprintType)
class VAMPIRESURVIVORCLONE_API AProjectileHoming : public AVampireSurvivorEffectActor
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
	
public:
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UProjectileMovementComponent> ProjectileMovement;

protected:
	UFUNCTION()
	void OnSphereOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void Tick(float DeltaSeconds) override;

public:
	UFUNCTION()
	void OnSphereHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);
	// Sets default values for this actor's properties
	AProjectileHoming();

	void Initialize(const bool InbBlockedByWalls, const float InSpeed, const float InPierce, const float InDamage,
		const float InArea, const TObjectPtr<const	AActor>& InHomingTargetActor, const TObjectPtr<AActor>& InAvatarActor);
};
