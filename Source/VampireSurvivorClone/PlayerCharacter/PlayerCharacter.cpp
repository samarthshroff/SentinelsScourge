// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCharacter.h"

#include "PlayerCharacterController.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "../WeaponActor.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"

APlayerCharacter::APlayerCharacter()
{
	GetCapsuleComponent()->SetCapsuleHalfHeight(96.0f);
	GetCapsuleComponent()->SetCapsuleRadius(42.0f);
	
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
		
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom);

	// Don't use rotation by player controller but use the one I set manually
	bUseControllerRotationYaw = false;
	// Make sure movement component rotates character to match input direction
	if (UCharacterMovementComponent* MovementComponent = GetCharacterMovement())
	{
		MovementComponent->bOrientRotationToMovement = false; // Disable movement-based rotation
	}
	// CameraBoom->TargetArmLength = 1500.0f;
	// CameraBoom->SetWorldRotation(FRotator(-50.0f, 0, 0));
	// FollowCamera->FieldOfView = 55.0f;
}

void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
	if (WeaponClass)
	{
		WeaponActor = GetWorld()->SpawnActor<AWeaponActor>(WeaponClass);
		WeaponActor->AttachToComponent(GetMesh(),FAttachmentTransformRules::KeepRelativeTransform, "WeaponSocket");
	}	
	if (WeaponActor != nullptr && CurrentWeaponMesh != nullptr)
	{
		WeaponActor->SetSkeletalMesh(CurrentWeaponMesh);
	}
	if (APlayerCharacterController* PlayerController = Cast<APlayerCharacterController>(Controller))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = 
		ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(MappingContext, 0);
		}
	}
}

void APlayerCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &APlayerCharacter::FollowClick);	
					
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Started, this, &APlayerCharacter::ClickStart);				
	}
}

void APlayerCharacter::FollowClick(const FInputActionValue& Value)
{
	if (APlayerCharacterController* PlayerController = Cast<APlayerCharacterController>(Controller))
	{
		PlayerController->ClickTriggered(Value);
	}
}

void APlayerCharacter::ClickStart(const FInputActionValue& Value)
{
}

