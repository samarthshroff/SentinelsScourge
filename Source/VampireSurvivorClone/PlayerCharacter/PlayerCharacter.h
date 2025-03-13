// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../CharacterBase.h"
#include "InputAction.h"
#include "PlayerCharacter.generated.h"

class AWeaponActor;
class UInputMappingContext;
class UInputAction;

UCLASS()
class VAMPIRESURVIVORCLONE_API APlayerCharacter : public ACharacterBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=CameraSettings, meta=(AllowPrivateAccess=true))
	USpringArmComponent* CameraBoom;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=CameraSettings, meta=(AllowPrivateAccess=true))
	UCameraComponent* FollowCamera;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	UInputMappingContext* MappingContext;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	UInputAction* MoveAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Weapon, meta=(AllowPrivateAccess=true))
	TSubclassOf<AWeaponActor> WeaponClass;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Weapon, meta=(AllowPrivateAccess=true))
	AWeaponActor* WeaponActor;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category=Weapon, meta=(AllowPrivateAccess=true))
	USkeletalMesh* CurrentWeaponMesh;

protected:
	// Called when the game starts or when spawned
	void BeginPlay() override;

public:
	APlayerCharacter();
	// Called every frame
	//virtual void Tick(float DeltaTime) override;

	
	// Called to bind functionality to input
	void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void FollowClick(const FInputActionValue& Value);	
	void ClickStart(const FInputActionValue& Value);	
};
