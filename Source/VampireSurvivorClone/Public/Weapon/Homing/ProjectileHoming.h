// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "../WeaponCategoryInterface.h"
#include "GameFramework/Actor.h"
#include "ProjectileHoming.generated.h"

class UProjectileMovementComponent;
class USphereComponent;

UCLASS(Blueprintable, BlueprintType)
class VAMPIRESURVIVORCLONE_API AProjectileHoming : public AActor, public IWeaponCategoryInterface
{
	GENERATED_BODY()
	
private:
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<USphereComponent> Sphere;

	// Can be replaced with the set of values needed. Will do it once it is confirmed
	// which values will be used.
	UPROPERTY()
	TObjectPtr<UWeaponAttributeSet> AttributeSet;

	UPROPERTY()
	TObjectPtr<const AActor> HomingTargetActor;

	UPROPERTY()
	TObjectPtr<const AActor> AvatarActor;

	bool bIsBlockedByWalls = false;

	float Speed;
	float Pierce;
	float Damage;
	float PierceCount;
	
public:
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UProjectileMovementComponent> ProjectileMovement;

protected:
	UFUNCTION()
	void OnSphereOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	
	virtual void Activate() override;
	virtual void DeActivate() override;

	virtual void Tick(float DeltaSeconds) override;

public:
	// Sets default values for this actor's properties
	AProjectileHoming();

	void Initialize(bool InbBlockedByWalls, float InSpeed, float InPierce, float InDamage, TObjectPtr<AActor> InHomingTargetActor);//TObjectPtr<UWeaponAttributeSet> InWeaponAttributes, const 
    	// FGameplayTag& 
    	// InWeaponTag) 
    	// override;
};
