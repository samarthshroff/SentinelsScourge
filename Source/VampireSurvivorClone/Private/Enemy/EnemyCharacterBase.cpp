// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy/EnemyCharacterBase.h"

#include "AbilitySystemComponent.h"
#include "Enemy/EnemyBehaviorTree/EnemyAIController.h"
#include "VampireSurvivorCloneGameMode.h"
#include "AbilitySystem/VSAbilitySystemComponent.h"
#include "AbilitySystem/EnemyAttributeSet.h"
#include "AbilitySystem/PlayerAttributeSet.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

AEnemyCharacterBase::AEnemyCharacterBase()
{
	CapsuleComp = GetCapsuleComponent();
	CapsuleComp->SetHiddenInGame(false);

	AIControllerClass = AEnemyAIController::StaticClass();
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;

	// AbilitySystemComponent = CreateDefaultSubobject<UVSAbilitySystemComponent>("AbilitySystemComponent");
	// AbilitySystemComponent->SetIsReplicated(false);
	// AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Minimal);	
	//
	// AttributeSet = CreateDefaultSubobject<UEnemyAttributeSet>("AttributeSet");	
	
	if (SkeletalMeshComponent == nullptr)
	{
		SkeletalMeshComponent = GetMesh();	
	}	
}

void AEnemyCharacterBase::BeginPlay()
{
	Super::BeginPlay();
	
	GetCharacterMovement()->MaxWalkSpeed = 200.0f;
	
	//AbilitySystemComponent->InitAbilityActorInfo(this, this);
	
	if (SkeletalMeshComponent)
	{
		// Get the scaled bounds of the skeletal mesh
		FBoxSphereBounds MeshBounds = SkeletalMeshComponent->Bounds;
		FVector MeshExtent = MeshBounds.BoxExtent;  // Half extents (X, Y, Z)
		FVector MeshScale = SkeletalMeshComponent->GetComponentScale(); // Scale of the mesh
		
		// Scale the extents
		FVector ScaledExtent = MeshExtent * MeshScale;

		// Calculate the new capsule radius (largest of X and Y extents)
		float NewRadius = FMath::Max(ScaledExtent.X, ScaledExtent.Y);
		float NewHalfHeight = ScaledExtent.Z;

		// Adjust the capsule component height and radius as per the skeletal mesh height and thickness.
		CapsuleComp->SetCapsuleHalfHeight(NewHalfHeight);
		CapsuleComp->SetCapsuleRadius(NewRadius);

		/*UE_LOG(LogTemp, Log, TEXT("MeshBounds.Origin %s, MeshScale %s"), *MeshBounds.Origin.ToString(), *MeshScale.ToString());
		UE_LOG(LogTemp, Log, TEXT("CapsuleComp.Origin %s"), *CapsuleComp->Bounds.Origin.ToString());
		
		UE_LOG(LogTemp, Log, TEXT("SM World Location %s and Cap World Location %s"), 
		*SkeletalMeshComponent->GetComponentLocation().ToString(),*CapsuleComp->GetComponentLocation().ToString());*/

		FVector MeshOffset = FVector(0.0f, 0.0f, SkeletalMeshComponent->GetRelativeLocation().Z -
			((MeshBounds.Origin.Z - CapsuleComp->Bounds.Origin.Z)*MeshScale.Z));
		// Bring the skeletal mesh inside the capsule.
		SkeletalMeshComponent->SetRelativeLocation(MeshOffset);
		
		/*DrawDebugLine(GetWorld(), MeshBounds.Origin,
		FVector(MeshBounds.Origin.X*50.0f, MeshBounds.Origin.Y, MeshBounds.Origin.Z),
		FColor::Red,
		true,
		1000.0f,
		0,
		2.0f);

		FVector sl = SkeletalMeshComponent->GetComponentLocation();
		DrawDebugLine(GetWorld(), sl,
		FVector(sl.X*50.0f, sl.Y, sl.Z),
		FColor::Green,
		true,
		1000.0f,
		0,
		2.0f);

		DrawDebugLine(GetWorld(), CapsuleComp->Bounds.Origin,
		FVector(CapsuleComp->Bounds.Origin.X*50.0f, CapsuleComp->Bounds.Origin.Y, CapsuleComp->Bounds.Origin.Z),
		FColor::Blue,
		true,
		1000.0f,
		0,
		2.0f);

		DrawDebugLine(GetWorld(), GetActorLocation(),
		GetActorLocation() + (GetActorForwardVector()*100.0f),
		FColor::Red,
		true,
		1000.0f,
		0,
		5.0f);*/
		
		// Let the Skeletal mesh face the same direction as the forward vector.
		// Hard-coded offset rotation (adjust these values based on how the mesh was exported)
		FRotator MeshAlignmentOffset = FRotator(0.0f, -90.0f, 0.0f); // Example: adjust as needed
		
		// Apply the adjustment
		SkeletalMeshComponent->SetRelativeRotation(MeshAlignmentOffset);

		/*DrawDebugLine(GetWorld(), MeshBounds.Origin,
		FVector(MeshBounds.Origin.X+1000.0f,MeshBounds.Origin.Y,MeshBounds.Origin.Z),
		FColor::Red,
		true,
		1000.0f,
		0,
		2.0f);
		MeshBounds = SkeletalMeshComponent->Bounds;
		MeshExtent = MeshBounds.BoxExtent;  // Half extents (X, Y, Z)
		MeshScale = SkeletalMeshComponent->GetComponentScale(); // Scale of the mesh
		
		// Scale the extents
		ScaledExtent = MeshExtent * MeshScale;
		DrawDebugBox(GetWorld(), MeshBounds.Origin, MeshBounds.BoxExtent, FColor::Blue,true,1000.0f,0,2.0f);
		DrawDebugBox(GetWorld(), MeshBounds.Origin, ScaledExtent, FColor::Yellow,true,1000.0f,0,1.0f);
		DrawDebugSphere(GetWorld(), MeshBounds.Origin, MeshBounds.SphereRadius, 8.0f,FColor::Green,true,1000.0f,0,2.0f);*/
	}

	/*FVector StartLocation = GetActorLocation();
	FVector ActorForward = GetActorForwardVector();
	DrawDebugLine(GetWorld(), StartLocation,
	StartLocation + (ActorForward*100.0f),//FVector(ActorForward.X+100.0f, ActorForward.Y, ActorForward.Z),
	FColor::Green,
	true,
	1000.0f,
	0,
	2.0f);

	FVector SKStartLocation = SkeletalMeshComponent->GetComponentLocation();
	FVector SKActorForward = SkeletalMeshComponent->GetForwardVector();
	DrawDebugLine(GetWorld(), SKStartLocation,
	SKStartLocation + (SKActorForward*100.0f),//FVector(ActorForward.X+100.0f, ActorForward.Y, ActorForward.Z),
	FColor::Red,
	true,
	1000.0f,
	0,
	2.0f);*/
	
	
	// Logic to make the actor touch the land/ground after being spawned.
	// Ignore the Land trace channel collision.
	SkeletalMeshComponent->SetCollisionResponseToChannel(LAND_CHANNEL, ECR_Ignore);
	FVector ActorLocation = GetActorLocation();
	// So that the line trace does not consider this actor as the actor hit.
	FCollisionQueryParams CollisionQueryParams(FName(TEXT("LandTrace")), false, this);
	FHitResult Hit;

	/*DrawDebugLine(
		GetWorld(),
		ActorLocation,
		FVector(ActorLocation.X, ActorLocation.Y, ActorLocation.Z - 1000.0f),
		FColor::Green,
		false, 5.0f, 0, 2.0f
	);*/
	
	if (GetWorld()->LineTraceSingleByChannel(Hit,ActorLocation,
		FVector(ActorLocation.X, ActorLocation.Y, ActorLocation.Z - 1000.0f), LAND_CHANNEL, CollisionQueryParams))
	{
		// UE_LOG(LogTemp, Log, TEXT("Hit.Location %s, Hit.Impact %s, HitActor %s"), *Hit.Location.ToString(), *Hit.ImpactPoint.ToString(),
		// 	*Hit.GetActor()->GetName());

		// The actor is half below the ground. this adjusts it's position.
		if (CapsuleComp)
		{
			float CapsuleHalfHeight = CapsuleComp->GetScaledCapsuleHalfHeight();
			FVector AdjustedLocation = Hit.Location + FVector(0.0f,0.0f,CapsuleHalfHeight);
			SetActorLocation(AdjustedLocation);
		}
	}	
}

void AEnemyCharacterBase::UpdateProperties(const FGameplayTag& EnemyTag, const float EnemySpeed, const float EnemyHealth, const float EnemyDamage,
		const float EnemyDistanceFromPlayerCharacter,	const TObjectPtr<UClass>& AnimInstancePtr, const TObjectPtr<USkeletalMesh>& SkeletalMesh,
		FVector PlayerMeshScale)
{
	this->Tag = EnemyTag;
	this->Speed = EnemySpeed;
	this->Health = EnemyHealth;
	this->Damage = EnemyDamage;
	this->DistanceFromPlayerCharacter = EnemyDistanceFromPlayerCharacter;
	
	if (SkeletalMeshComponent == nullptr)
	{
		SkeletalMeshComponent = GetMesh();	
	}
	
	if (SkeletalMeshComponent)
	{
		SkeletalMeshComponent->SetSkeletalMesh(SkeletalMesh.Get());
		SkeletalMeshComponent->SetAnimInstanceClass(AnimInstancePtr.Get());
		SkeletalMeshComponent->SetRelativeScale3D(PlayerMeshScale);
	}
}

void AEnemyCharacterBase::UpdateWalkSpeed(float NewSpeed)
{
	GetCharacterMovement()->MaxWalkSpeed = NewSpeed;
}

void AEnemyCharacterBase::UpdateCurrentState(UEnemyStates NewState)
{
	this->CurrentState = NewState;
}
