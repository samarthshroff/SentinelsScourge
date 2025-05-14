// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayEffectTypes.h"
#include "Character/CharacterBase.h"
#include "GameplayTagContainer.h"
#include "EnemyStates.h"
#include "EnemyCharacterBase.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnEnemyActorStateChanged, UEnemyStates, State);

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

	UPROPERTY()
	TObjectPtr<UAnimMontage> AnimMontageDie;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Component, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<USkeletalMeshComponent> SkeletalMeshComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Component, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UCapsuleComponent> CapsuleComp;

	FActiveGameplayEffectHandle DefaultAttributesEffectHandle;

	FDelegateHandle AttributeChangeDelegateHandle;

public:
	FGameplayTag Tag;

	// TODO - Revisit this event. May not need it after all.
	UPROPERTY(BlueprintAssignable)
	FOnEnemyActorStateChanged OnEnemyActorStateChanged;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void BeginDestroy() override;

public:
	AEnemyCharacterBase();
	//Passing by reference avoids copying the TObjectPtr object, which is more efficient.
	//Using const& ensures the function cannot modify the TObjectPtr itself (i.e., it can't assign it to point to a different SkeletalMesh).
	void UpdateProperties(const FGameplayTag& InEnemyTag, const float InEnemyDistanceFromPlayerCharacter, const FVector& InPlayerMeshScale,
		const TObjectPtr<UClass>& InAnimInstancePtr, const TObjectPtr<UAnimMontage>& InAnimMontageDie, const TObjectPtr<USkeletalMesh>& InSkeletalMesh,
		const TSubclassOf<UGameplayEffect>& InDefaultAttributesClass);

	void UpdateWalkSpeed(float NewSpeed) const;
	void UpdateCurrentState(UEnemyStates NewState);
	virtual FGameplayTag GetCharacterTag() const override;
	virtual bool TagExactExistsInAbilityComponent(const FGameplayTag InTag) const override;
	virtual bool IsCharacterAlive() const override;

	//virtual float TakeDamage(float DamageTaken, const FDamageEvent& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;

	UFUNCTION()
	void OnAnimMontageDieComplete(UAnimMontage* Montage, bool bInterrupted);
	void AttributeChanged(const FOnAttributeChangeData& OnAttributeChangeData);
	virtual void PossessedBy(AController* NewController) override;
	virtual void InitAbilityActorInfo() override;
	virtual UAttributeSet* GetAttributeSetComponent() const override;
};


