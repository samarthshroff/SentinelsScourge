// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/CharacterBase.h"
#include "InputAction.h"
#include "PlayerCharacter.generated.h"

class UVSWidget;
class UPlayerHealthBarWidgetComponent;
class AVSCProgressBarWidgetActor;
class UWidgetComponent;
class APlayerCharacterState;
class AWeaponActor;
class UInputMappingContext;
class UInputAction;

UCLASS()
class VAMPIRESURVIVORCLONE_API APlayerCharacter : public ACharacterBase
{
	GENERATED_BODY()

private:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=CameraSettings, meta=(AllowPrivateAccess=true))
	TObjectPtr<USpringArmComponent> CameraBoom;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=CameraSettings, meta=(AllowPrivateAccess=true))
	TObjectPtr<UCameraComponent> FollowCamera;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	TObjectPtr<UInputMappingContext> MappingContext;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	TObjectPtr<UInputAction> MoveAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Weapon, meta=(AllowPrivateAccess=true))
	TSubclassOf<AWeaponActor> WeaponClass;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Weapon, meta=(AllowPrivateAccess=true))
	TObjectPtr<AWeaponActor> WeaponActor;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category=Weapon, meta=(AllowPrivateAccess=true))
	TObjectPtr<UStaticMesh> DefaultWeaponMesh;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category=UI, meta=(AllowPrivateAccess=true))
	TObjectPtr<UPlayerHealthBarWidgetComponent> HealthBar;
		
public:
	APlayerCharacter();	
	// Called every frame	
	//virtual void Tick(float DeltaTime) override;
	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	virtual void PossessedBy(AController* NewController) override;
	virtual int32 GetCharacterLevel() override;
	virtual FGameplayTag GetCharacterTag() const override;

protected:
	// Called when the game starts or when spawned
	void BeginPlay() override;

	virtual void InitAbilityActorInfo() override;
	
private:
	void OnLevelChanged(int32 NewLevel);
	void OnMoveActionButtonHeld(const FInputActionValue& Value);	
	void OnMoveActionButtonPressed(const FInputActionValue& Value);
	void OnMoveActionButtonReleased(const FInputActionValue& InputActionValue);

};
