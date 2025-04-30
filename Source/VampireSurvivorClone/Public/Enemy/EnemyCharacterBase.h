// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/CharacterBase.h"
#include "GameplayTagContainer.h"
#include "EnemyCharacterBase.generated.h"

enum class UEnemyStates : uint8;
/**
 * 
 */
UCLASS()
class VAMPIRESURVIVORCLONE_API AEnemyCharacterBase : public ACharacterBase
{
	GENERATED_BODY()

private:
	float Speed;
	float Health;
	float Damage;
	float DistanceFromPlayerCharacter;
	UEnemyStates CurrentState;
	
	TUniquePtr<UAnimInstance> AnimInstance;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Component, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<USkeletalMeshComponent> SkeletalMeshComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Component, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UCapsuleComponent> CapsuleComp;

public:
	FGameplayTag Tag;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	AEnemyCharacterBase();
	//Passing by reference avoids copying the TObjectPtr object, which is more efficient.
	//Using const& ensures the function cannot modify the TObjectPtr itself (i.e., it can't assign it to point to a different SkeletalMesh).
	void UpdateProperties(const FGameplayTag& EnemyTag, const float EnemySpeed, const float EnemyHealth,
		const float	EnemyDamage, const float EnemyDistanceFromPlayerCharacter, const TObjectPtr<UClass>& AnimInstancePtr, const TObjectPtr<USkeletalMesh>& SkeletalMesh,
		FVector PlayerMeshScale);

	void UpdateWalkSpeed(float NewSpeed);
	void UpdateCurrentState(UEnemyStates NewState);
};
