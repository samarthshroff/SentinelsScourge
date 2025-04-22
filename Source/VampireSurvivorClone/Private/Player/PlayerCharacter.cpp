// Fill out your copyright notice in the Description page of Project Settings.


#include "VampireSurvivorClone/Public/Player/PlayerCharacter.h"

#include "AbilitySystemComponent.h"
#include "AttributeSet.h"
#include "VampireSurvivorClone/Public/Player/PlayerCharacterController.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "MovieSceneTracksComponentTypes.h"
#include "WeaponActor.h"
#include "AbilitySystem/PlayerAttributeSet.h"
#include "Components/WidgetComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "Player/PlayerCharacterState.h"
#include "UI/HUD/VSHUD.h"
#include "UI/WidgetComponent/PlayerHealthBarWidgetComponent.h"
#include "UI/WidgetController/VSCWidgetController.h"

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

	HealthBar = CreateDefaultSubobject<UPlayerHealthBarWidgetComponent>(TEXT("HealthBar"));
	HealthBar->SetupAttachment(RootComponent);

	//,FAttachmentTransformRules::KeepRelativeTransform);
	// CameraBoom->TargetArmLength = 1500.0f;
	// CameraBoom->SetWorldRotation(FRotator(-50.0f, 0, 0));
	// FollowCamera->FieldOfView = 55.0f;
}

// void APlayerCharacter::Tick(float DeltaTime)
// {
// 	Super::Tick(DeltaTime);	
// }

void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
	UE_LOG(LogTemp, Log, TEXT("APlayerCharacter::BeginPlay"));
		
	if (WeaponClass)
	{
		WeaponActor = GetWorld()->SpawnActor<AWeaponActor>(WeaponClass);
		WeaponActor->AttachToComponent(GetMesh(),FAttachmentTransformRules::KeepRelativeTransform, "WeaponSocket");
	}	
	if (WeaponActor != nullptr && DefaultWeaponMesh != nullptr)
	{
		WeaponActor->SetStaticMesh(DefaultWeaponMesh);
	}
	if (APlayerCharacterController* PlayerController = Cast<APlayerCharacterController>(Controller))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = 
		ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(MappingContext, 0);
		}

		const FWidgetControllerParams WidgetControllerParams(PlayerController, GetPlayerState<APlayerCharacterState>(),
		AbilitySystemComponent, AttributeSet);
		/*Calling it here based on the execution order
		 * UPlayerHealthBarWidgetComponent::OnRegister
		 * APlayerCharacter::PossessedBy
		 * UPlayerHealthBarWidgetComponent::BeginPlay
		 * APlayerCharacter::BeginPlay
		 * UPlayerHealthBarWidgetComponent::Initialize
		 * Might not be idle for multiplayer but works for single player (KISS)
		 */
		if (HealthBar)
		{
			HealthBar->Initialize(WidgetControllerParams);				
		}

		AVSHUD* HUD = Cast<AVSHUD>(UGameplayStatics::GetPlayerController(GetWorld(), 0)->GetHUD());
		if (HUD)
		{
			HUD->Initialize(WidgetControllerParams);
		}
	}
}

void APlayerCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &APlayerCharacter::OnMoveActionButtonHeld);					
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Started, this, &APlayerCharacter::OnMoveActionButtonPressed);				
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Completed, this,&APlayerCharacter::OnMoveActionButtonReleased);
						
	}
}

void APlayerCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	UE_LOG(LogTemp, Log, TEXT("HealthBar APlayerCharacter::PossessedBy"));
	APlayerCharacterState* VampireSurvivorPlayerState = GetPlayerState<APlayerCharacterState>();
	
	AbilitySystemComponent = VampireSurvivorPlayerState->GetAbilitySystemComponent();
	AttributeSet = VampireSurvivorPlayerState->GetAttributeSetComponent();
	AbilitySystemComponent->InitAbilityActorInfo(VampireSurvivorPlayerState, this);

	GetPlayerState<APlayerCharacterState>()->Initialize();	
	InitializeAttributes();
	float MH = Cast<UPlayerAttributeSet>(AttributeSet)->GetMaxHealth();
	float H = Cast<UPlayerAttributeSet>(AttributeSet)->GetHealth();
	UE_LOG(LogTemp, Log, TEXT("APlayerCharacter::BeginPlay() the MaxHealth is %f and Health is %f"), MH,H);
	GetPlayerState<APlayerCharacterState>()->PlayerLevelChanged.AddUObject(this, &APlayerCharacter::OnLevelChanged);
}

void APlayerCharacter::OnMoveActionButtonHeld(const FInputActionValue& Value)
{
	if (APlayerCharacterController* PlayerController = Cast<APlayerCharacterController>(Controller))
	{
		PlayerController->MoveButtonHeld(Value);
	}
}

void APlayerCharacter::OnMoveActionButtonPressed(const FInputActionValue& Value)
{
	if (APlayerCharacterController* PlayerController = Cast<APlayerCharacterController>(Controller))
	{
		PlayerController->MoveButtonPressed(Value);
	}
}

void APlayerCharacter::OnMoveActionButtonReleased(const FInputActionValue& Value)
{
	if (APlayerCharacterController* PlayerController = Cast<APlayerCharacterController>(Controller))
	{
		PlayerController->MoveButtonReleased(Value);
	}
}

int32 APlayerCharacter::GetCharacterLevel()
{
	return GetPlayerState<APlayerCharacterState>()->GetCurrentLevel();
}

FGameplayTag APlayerCharacter::GetCharacterTag() const
{
	return GetPlayerState<APlayerCharacterState>()->GetCurrentHeroTag();
}

void APlayerCharacter::OnLevelChanged(int32 NewLevel)
{

}

