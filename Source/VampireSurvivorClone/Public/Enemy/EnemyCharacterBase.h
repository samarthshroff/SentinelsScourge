// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayEffectTypes.h"
#include "Character/CharacterBase.h"
#include "GameplayTagContainer.h"
#include "EnemyCharacterBase.generated.h"

enum class UEnemyStates : uint8;
/**
 * Base class for all the enemies.
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

	FActiveGameplayEffectHandle DefaultAttributesEffectHandle;

public:
	FGameplayTag Tag;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	AEnemyCharacterBase();
	//Passing by reference avoids copying the TObjectPtr object, which is more efficient.
	//Using const& ensures the function cannot modify the TObjectPtr itself (i.e., it can't assign it to point to a different SkeletalMesh).
	void UpdateProperties(const FGameplayTag& EnemyTag, const float EnemyDistanceFromPlayerCharacter, FVector PlayerMeshScale,
		const TObjectPtr<UClass>& AnimInstancePtr, const TObjectPtr<USkeletalMesh>& SkeletalMesh, TSubclassOf<UGameplayEffect> InDefaultAttributesClass);

	void UpdateWalkSpeed(float NewSpeed) const;
	void UpdateCurrentState(UEnemyStates NewState);
	virtual FGameplayTag GetCharacterTag() const override;

	//virtual float TakeDamage(float DamageTaken, const FDamageEvent& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;

	void AttributeChanged(const FOnAttributeChangeData& OnAttributeChangeData);
	virtual void PossessedBy(AController* NewController) override;
	virtual void InitAbilityActorInfo() override;
};


