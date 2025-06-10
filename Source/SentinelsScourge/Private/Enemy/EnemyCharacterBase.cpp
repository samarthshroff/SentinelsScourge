// Fill out your copyright notice in the Description page of Project Settings.

#include "Enemy/EnemyCharacterBase.h"

#include "AbilitySystemComponent.h"
#include "BrainComponent.h"
#include "GameplayEffectExtension.h"
#include "Enemy/EnemyBehaviorTree/EnemyAIController.h"
#include "SentinelsScourgeGameMode.h"
#include "SentinelsScourgeGameplayTags.h"
#include "AbilitySystem/EnemyAttributeSet.h"
#include "AbilitySystem/EnemyHitGEContext.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

AEnemyCharacterBase::AEnemyCharacterBase()
{
	CapsuleComp = GetCapsuleComponent();
	CapsuleComp->SetHiddenInGame(true);
	CapsuleComp->SetCollisionObjectType(ECC_EnemyChannel);

	AIControllerClass = AEnemyAIController::StaticClass();
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;

	AbilitySystemComponent = CreateDefaultSubobject<UAbilitySystemComponent>("AbilitySystemComponent");
	AbilitySystemComponent->SetIsReplicated(false);
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Full);
	AttributeSet = CreateDefaultSubobject<UEnemyAttributeSet>("AttributeSet");

	if (SkeletalMeshComponent == nullptr)
	{
		SkeletalMeshComponent = GetMesh();
	}

	// SkeletalMeshComponent->SetSimulatePhysics(true);
	//  Used for weapon collision with enemy actors. Have to add it from here as
	//  I cannot grant tags via Instant GE used for setting attributes' default values.
	AbilitySystemComponent->AddLooseGameplayTag(SentinelsScourgeGameplayTags::Enemy_Root);
}

void AEnemyCharacterBase::BeginPlay()
{
	Super::BeginPlay();

	GetCharacterMovement()->MaxWalkSpeed = 200.0f;

	// TODO - use this function for scenarios where we don't want enemies to be damaged.
	SetCanBeDamaged(true);

	// AbilitySystemComponent->InitAbilityActorInfo(this, this);
	CapsuleComp->SetCollisionResponseToChannel(ECC_ProjectileChannel, ECR_Overlap);
	if (SkeletalMeshComponent)
	{
		// Get the scaled bounds of the skeletal mesh
		FBoxSphereBounds MeshBounds = SkeletalMeshComponent->Bounds;
		FVector MeshExtent = MeshBounds.BoxExtent;						// Half extents (X, Y, Z)
		FVector MeshScale = SkeletalMeshComponent->GetComponentScale(); // Scale of the mesh

		// Scale the extents
		FVector ScaledExtent = MeshExtent * MeshScale;

		// Calculate the new capsule radius (largest of X and Y extents)
		float NewRadius = FMath::Max(ScaledExtent.X, ScaledExtent.Y);
		float NewHalfHeight = ScaledExtent.Z;

		// Adjust the capsule component height and radius as per the skeletal mesh height and thickness.
		CapsuleComp->SetCapsuleHalfHeight(NewHalfHeight);
		CapsuleComp->SetCapsuleRadius(NewRadius);

		FVector MeshOffset = FVector(0.0f, 0.0f, SkeletalMeshComponent->GetRelativeLocation().Z - ((MeshBounds.Origin.Z - CapsuleComp->Bounds.Origin.Z) * MeshScale.Z));
		// Bring the skeletal mesh inside the capsule.
		SkeletalMeshComponent->SetRelativeLocation(MeshOffset);

		// Let the Skeletal mesh face the same direction as the forward vector.
		// Hard-coded offset rotation (adjust these values based on how the mesh was exported)
		FRotator MeshAlignmentOffset = FRotator(0.0f, -90.0f, 0.0f); // Example: adjust as needed

		// Apply the adjustment
		SkeletalMeshComponent->SetRelativeRotation(MeshAlignmentOffset);
	}

	// Logic to make the actor touch the land/ground after being spawned.
	// Ignore the Land trace channel collision.

	SkeletalMeshComponent->SetCollisionResponseToChannel(ECC_LandChannel, ECR_Ignore);
	FVector ActorLocation = GetActorLocation();
	// So that the line trace does not consider this actor as the actor hit.
	FCollisionQueryParams CollisionQueryParams(FName(TEXT("LandTrace")), false, this);
	FHitResult Hit;

	if (GetWorld()->LineTraceSingleByChannel(Hit, ActorLocation,
											 FVector(ActorLocation.X, ActorLocation.Y, ActorLocation.Z - 1000.0f), ECC_LandChannel, CollisionQueryParams))
	{
		// UE_LOG(LogTemp, Log, TEXT("Hit.Location %s, Hit.Impact %s, HitActor %s"), *Hit.Location.ToString(), *Hit.ImpactPoint.ToString(),
		// 	*Hit.GetActor()->GetName());

		// The actor is half below the ground. this adjusts it's position.
		if (CapsuleComp)
		{
			float CapsuleHalfHeight = CapsuleComp->GetScaledCapsuleHalfHeight();
			FVector AdjustedLocation = Hit.Location + FVector(0.0f, 0.0f, CapsuleHalfHeight);
			SetActorLocation(AdjustedLocation);
		}
	}
}

void AEnemyCharacterBase::UpdateProperties(const FGameplayTag &InEnemyTag, const float InEnemyDistanceFromPlayerCharacter, const FVector &InPlayerMeshScale,
										   const TObjectPtr<UClass> &InAnimInstancePtr, const TObjectPtr<UAnimMontage> &InAnimMontageDie, const TObjectPtr<USkeletalMesh> &InSkeletalMesh,
										   const TSubclassOf<UGameplayEffect> &InDefaultAttributesClass)
{
	Tag = InEnemyTag;
	DistanceFromPlayerCharacter = InEnemyDistanceFromPlayerCharacter;
	DefaultAttributes = InDefaultAttributesClass;
	AnimMontageDie = InAnimMontageDie;

	if (SkeletalMeshComponent == nullptr)
	{
		SkeletalMeshComponent = GetMesh();
	}

	if (SkeletalMeshComponent)
	{
		SkeletalMeshComponent->SetSkeletalMesh(InSkeletalMesh.Get());
		SkeletalMeshComponent->SetAnimInstanceClass(InAnimInstancePtr.Get());
		SkeletalMeshComponent->SetRelativeScale3D(InPlayerMeshScale);
	}
}

void AEnemyCharacterBase::InitAbilityActorInfo()
{
	AbilitySystemComponent->InitAbilityActorInfo(this, this);
}

UAttributeSet *AEnemyCharacterBase::GetAttributeSetComponent() const
{
	return AttributeSet;
}

void AEnemyCharacterBase::PossessedBy(AController *NewController)
{
	Super::PossessedBy(NewController);
	InitAbilityActorInfo();
	InitializeAttributes();

	if (UEnemyAttributeSet *AS = Cast<UEnemyAttributeSet>(AttributeSet))
	{
		UpdateWalkSpeed(AS->GetSpeed());
		AttributeChangeDelegateHandle = AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AS->GetHealthAttribute()).AddUObject(this, &AEnemyCharacterBase::AttributeChanged);
	}
}

void AEnemyCharacterBase::AttributeChanged(const FOnAttributeChangeData &OnAttributeChangeData)
{
	// UE_LOG(LogTemp, Log, TEXT("The Enemy Old Health was:: %f and New Health is:: %f"), OnAttributeChangeData.OldValue, OnAttributeChangeData.NewValue);

	if (UEnemyAttributeSet *EAS = Cast<UEnemyAttributeSet>(AttributeSet))
	{
		if (OnAttributeChangeData.Attribute == EAS->GetHealthAttribute())
		{
			// check if health is > 0
			// No - play die animation (if not too much load on system) and destroy the actor
			// Yes - calculate knockback and apply force, show damage on ui, tint the actor

			if (EAS->GetHealth() > 0)
			{
				// Get knockback value from the context handle.
				FGameplayEffectContextHandle ContextHandle = OnAttributeChangeData.GEModData->EffectSpec.GetContext();

				FEnemyHitGEContext *EnemyHitContext = static_cast<FEnemyHitGEContext *>(ContextHandle.Get());
				float InComingKnockback = EnemyHitContext->GetKnockback();
				AActor *SourceInstigator = EnemyHitContext->GetInstigator();

				FVector Direction = -1.0f * GetVelocity();
				FVector FinalKnockback = Direction * InComingKnockback * EAS->GetKnockback();
				AddActorWorldOffset(FinalKnockback, false);

				// AddActor
				// SkeletalMeshComponent->AddForce(FinalKnockback);
				//
			}
			else
			{
				AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(EAS->GetHealthAttribute()).Remove(AttributeChangeDelegateHandle);
				Cast<AEnemyAIController>(GetController())->BrainComponent->StopLogic("Dying");
				UpdateCurrentState(UEnemyStates::Dying);

				if (AnimMontageDie != nullptr)
				{
					UAnimInstance *CurrentInstance = SkeletalMeshComponent->GetAnimInstance();

					// Don't take root motion from Montage and play the animation in place.
					CurrentInstance->SetRootMotionMode(ERootMotionMode::Type::NoRootMotionExtraction);
					CurrentInstance->OnMontageEnded.AddDynamic(this, &AEnemyCharacterBase::OnAnimMontageDieComplete);
					float MontageDuration = CurrentInstance->Montage_Play(AnimMontageDie.Get());
				}
			}
		}
	}
}

void AEnemyCharacterBase::OnAnimMontageDieComplete(UAnimMontage *Montage, bool bInterrupted)
{
	CapsuleComp->SetCollisionEnabled(ECollisionEnabled::Type::NoCollision);
	SkeletalMeshComponent->SetCollisionEnabled(ECollisionEnabled::Type::NoCollision);
	SkeletalMeshComponent->GetAnimInstance()->OnMontageEnded.RemoveDynamic(this, &AEnemyCharacterBase::OnAnimMontageDieComplete);
	UpdateCurrentState(UEnemyStates::Dead);
	Destroy();
}

void AEnemyCharacterBase::UpdateWalkSpeed(const float NewSpeed) const
{
	GetCharacterMovement()->MaxWalkSpeed = NewSpeed;
}

void AEnemyCharacterBase::UpdateCurrentState(const UEnemyStates NewState)
{
	CurrentState = NewState;
	OnEnemyActorStateChanged.Broadcast(CurrentState);
	if (CurrentState == UEnemyStates::Dying)
	{
		OnCharacterBeingDestroyed.Broadcast(this);
	}
	if (CurrentState == UEnemyStates::Dead)
	{
		OnCharacterDestroyed.Broadcast(this);
	}
}

FGameplayTag AEnemyCharacterBase::GetCharacterTag() const
{
	return Tag;
}

bool AEnemyCharacterBase::TagExactExistsInAbilityComponent(const FGameplayTag InTag) const
{
	// if (CurrentState == UEnemyStates::Dying || CurrentState == UEnemyStates::Dead)
	// {
	// 	UE_LOG(LogTemp, Error, TEXT("Enemy Actor is up for Destroy. Returning False."));
	// 	return false;
	// }
	return Super::TagExactExistsInAbilityComponent(InTag);
}

bool AEnemyCharacterBase::IsCharacterAlive() const
{
	return (CurrentState != UEnemyStates::Dying && CurrentState != UEnemyStates::Dead);
}

void AEnemyCharacterBase::BeginDestroy()
{

	Super::BeginDestroy();
}

// float AEnemyCharacterBase::TakeDamage(float DamageTaken, const FDamageEvent& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
// {
// 	return Super::TakeDamage(DamageTaken, DamageEvent, EventInstigator, DamageCauser);
// }
