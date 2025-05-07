// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/Tasks/AbilityTask.h"
#include "AbilityTask_HomingProjectile.generated.h"

class UWeaponManager;
class USphereComponent;
class UWeaponAttributeSet;
class AProjectileHoming;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FHomingProjectileCompleteDelegate, bool, bWasSuccessful);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FHomingProjectileImpactDelegate, AActor*, TargetActor, FVector, ImpactLocation);

/**
 * 
 */
UCLASS()
class VAMPIRESURVIVORCLONE_API UAbilityTask_HomingProjectile : public UAbilityTask
{
	GENERATED_BODY()

private:
	float DefaultTargetingRadius;

	int ProjectilesToSpawn;
	
	UPROPERTY()
	TSubclassOf<AProjectileHoming> ProjectileClass;

	UPROPERTY()
	TObjectPtr<UWeaponAttributeSet> WeaponAttributeSet;

	UPROPERTY()
	TSet<TObjectPtr<AActor>> HitTargets;
	
	UPROPERTY()
	TObjectPtr<USphereComponent> TargetingSphere;

	UPROPERTY()
	FGameplayTag WeaponTag;

	UPROPERTY()
	TObjectPtr<UCurveTable> TargetingRadiusCurveTable;

	UPROPERTY()
	TObjectPtr<UWeaponManager> WeaponManager;

	// UPROPERTY()
	// TObjectPtr<AProjectileHoming> SpawnedProjectile;
	
public:
	// Delegates for blueprint callbacks
	UPROPERTY(BlueprintAssignable)
	FHomingProjectileCompleteDelegate OnComplete;
    
	UPROPERTY(BlueprintAssignable)
	FHomingProjectileImpactDelegate OnImpact;

private:
	void UpdateTargetingSphereRadius() const;
	
protected:
	virtual void TickTask(float DeltaTime) override;
	const AActor* FindClosestTarget() const;

	UFUNCTION()
	void OnTargetingSphereOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
	                              const FHitResult& SweepResult);
	
	void Initialize_Internal(const UGameplayAbility* OwningAbility, const FGameplayTag& InWeaponTag, const TSubclassOf<AProjectileHoming>& InProjectileClass, UWeaponManager* InWeaponManager);	
	
public:
	explicit UAbilityTask_HomingProjectile(const FObjectInitializer& ObjectInitializer);

	UFUNCTION(Blueprintable, Category="Ability|Tasks", meta = (HidePin = "OwningAbility", DefaultToSelf = "OwningAbility", BlueprintInternalUseOnly = "TRUE"))
	static UAbilityTask_HomingProjectile* CreateHomingProjectile(UGameplayAbility* OwningAbility, FName TaskInstanceName, const FGameplayTag& InWeaponTag,
		const TSubclassOf<AProjectileHoming>& InProjectileClass, UWeaponManager* InWeaponManager);

	void SpawnProjectile();

	virtual void OnDestroy(bool bInOwnerFinished) override;	
};
