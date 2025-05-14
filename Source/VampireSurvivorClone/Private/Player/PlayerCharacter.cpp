// Fill out your copyright notice in the Description page of Project Settings.


#include "VampireSurvivorClone/Public/Player/PlayerCharacter.h"

#include "AbilitySystemComponent.h"
#include "VampireSurvivorClone/Public/Player/PlayerCharacterController.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "VampireSurvivorCloneGameMode.h"
#include "VampireSurvivorGameplayTags.h"
#include "Weapon/WeaponActor.h"
#include "AbilitySystem/HeroAbilitySystemComponent.h"
#include "AbilitySystem/PlayerAttributeSet.h"
#include "AbilitySystem/VSAbilitySystemLibrary.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Player/PlayerCharacterState.h"
#include "UI/HUD/VSHUD.h"
#include "UI/WidgetComponent/PlayerHealthBarWidgetComponent.h"
#include "UI/WidgetController/VSCWidgetController.h"

APlayerCharacter::APlayerCharacter()
{
	GetCapsuleComponent()->SetCapsuleHalfHeight(96.0f);
	GetCapsuleComponent()->SetCapsuleRadius(42.0f);
	GetCapsuleComponent()->SetCollisionObjectType(ECC_PlayerCharacterChannel);
	
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
}

void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	if (WeaponClass)
	{
		WeaponActor = GetWorld()->SpawnActor<AWeaponActor>(WeaponClass);
		WeaponActor->AttachToComponent(GetMesh(),FAttachmentTransformRules::KeepRelativeTransform, "WeaponSocket");
		WeaponActor->SetActorEnableCollision(false);
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

void APlayerCharacter::InitAbilityActorInfo()
{
	APlayerCharacterState* VampireSurvivorPlayerState = GetPlayerState<APlayerCharacterState>();
	AbilitySystemComponent = VampireSurvivorPlayerState->GetAbilitySystemComponent();
	AttributeSet = VampireSurvivorPlayerState->GetAttributeSetComponent();
	AbilitySystemComponent->InitAbilityActorInfo(VampireSurvivorPlayerState, this);
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

	InitAbilityActorInfo();
	Cast<UHeroAbilitySystemComponent>(AbilitySystemComponent)->Initialize(WeaponDataAsset);

	GetPlayerState<APlayerCharacterState>()->Initialize();	
	InitializeAttributes();
	GetPlayerState<APlayerCharacterState>()->PlayerLevelChanged.AddUObject(this, &APlayerCharacter::OnLevelChanged);

	GiveAbility(VampireSurvivorGameplayTags::Weapon_Hero_MagicWand);	
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
		auto GTags = UVSAbilitySystemLibrary::GetAllGameplayTagsThatMatch("Weapon.Hero");
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

int32 APlayerCharacter::GetCharacterLevel() const
{
	return GetPlayerState<APlayerCharacterState>()->GetCurrentLevel();
}

FGameplayTag APlayerCharacter::GetCharacterTag() const
{
	return GetPlayerState<APlayerCharacterState>()->GetCurrentHeroTag();
}

int APlayerCharacter::GetWeaponLevel(const FGameplayTag& AbilityTag) const
{
	return 0;
}

bool APlayerCharacter::IsCharacterAlive() const
{
	return Cast<UPlayerAttributeSet>(AttributeSet)->GetHealth() > 0.0f;
}

void APlayerCharacter::OnLevelChanged(int32 NewLevel)
{

}

