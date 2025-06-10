// Copyright (c) Samarth Shroff. All Rights Reserved.
// This work is protected under applicable copyright laws in perpetuity.
// Licensed under the CC BY-NC-ND 4.0 License. See LICENSE file for details.

#pragma once

#include "CoreMinimal.h"
#include "Character/CharacterBase.h"
#include "InputAction.h"
#include "AbilitySystem/PlayerAttributeSet.h"
#include "PlayerCharacter.generated.h"

struct FOnAttributeChangeData;
class UWeaponAttributeSet;
class UMagicWandAttributeSet;
class USSWidget;
class UPlayerHealthBarWidgetComponent;
class ASSCProgressBarWidgetActor;
class UWidgetComponent;
class APlayerCharacterState;
class AWeaponActor;
class UInputMappingContext;
class UInputAction;

UCLASS()
class SENTINELSSCOURGE_API APlayerCharacter : public ACharacterBase
{
	GENERATED_BODY()

private:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = CameraSettings, meta = (AllowPrivateAccess = true))
	TObjectPtr<USpringArmComponent> CameraBoom;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = CameraSettings, meta = (AllowPrivateAccess = true))
	TObjectPtr<UCameraComponent> FollowCamera;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputMappingContext> MappingContext;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputAction> MoveAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Weapon, meta = (AllowPrivateAccess = true))
	TSubclassOf<AWeaponActor> WeaponClass;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Weapon, meta = (AllowPrivateAccess = true))
	TObjectPtr<AWeaponActor> WeaponActor;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Weapon, meta = (AllowPrivateAccess = true))
	TObjectPtr<UStaticMesh> DefaultWeaponMesh;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = UI, meta = (AllowPrivateAccess = true))
	TObjectPtr<UPlayerHealthBarWidgetComponent> HealthBar;

public:
	UPROPERTY()
	UWeaponAttributeSet *MagicWandSet;

	UPROPERTY()
	TSubclassOf<UWeaponAttributeSet> WeaponSet;

	APlayerCharacter();

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent *PlayerInputComponent) override;
	virtual void PossessedBy(AController *NewController) override;
	virtual int32 GetCharacterLevel() const override;
	virtual FGameplayTag GetCharacterTag() const override;
	virtual int GetWeaponLevel(const FGameplayTag &AbilityTag) const override;
	virtual bool IsCharacterAlive() const override;

	template <typename UserClass>
	inline void RegisterToHeroLevelAttributeChange(UserClass *InUserObject, void (UserClass::*InFunction)(const FOnAttributeChangeData &))
	{
		AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(Cast<UPlayerAttributeSet>(AttributeSet)->GetLevelAttribute()).AddUObject(InUserObject, InFunction);
	}

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void InitAbilityActorInfo() override;

private:
	void OnLevelChanged(const FOnAttributeChangeData &Data);
	void OnMoveActionButtonHeld(const FInputActionValue &Value);
	void OnMoveActionButtonPressed(const FInputActionValue &Value);
	void OnMoveActionButtonReleased(const FInputActionValue &InputActionValue);
};
