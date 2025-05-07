// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon/Homing/HomingTargetComponent.h"

#include "Character/CharacterBaseInterface.h"

// Sets default values for this component's properties
UHomingTargetComponent::UHomingTargetComponent(): DefaultTargetingRadius(0)
{
	bHiddenInGame = false;
}

void UHomingTargetComponent::Initialize(const FGameplayTag& InTag)
{
	WeaponTag = InTag;

	SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	SetCollisionResponseToAllChannels(ECR_Ignore);
	SetCollisionResponseToChannel(ECC_WorldDynamic, ECR_Overlap);
	SetCollisionResponseToChannel(ECC_WorldStatic, ECR_Overlap);
	SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);

	FVector2D Viewport = FVector2D::ZeroVector;
	GEngine->GameViewport->GetViewportSize(Viewport);

	DefaultTargetingRadius = FMath::Max(Viewport.X, Viewport.Y);
	SetSphereRadius(DefaultTargetingRadius);	
	
	OnComponentBeginOverlap.AddDynamic(this, &UHomingTargetComponent::OnTargetingSphereOverlap);
	
	TargetingRadiusCurveTable = LoadObject<UCurveTable>(this, TEXT("/Game/Blueprints/AbilitySystem/Abilities/Weapons/ProjectileHoming/CT_TargetingRadius.CT_TargetingRadius"));
	UpdateTargetingSphereRadius();
}

FVector UHomingTargetComponent::GetClosestActorLocation() const
{
	const FVector ActorLocation = GetOwner()->GetActorLocation();
	const FVector DirectionVector = GetOwner()->GetActorForwardVector();

	// If no closest enemy found then shoot in the direction of player facing and as far as possible
	FVector ClosestLocation = DirectionVector * 2000.0f;

	float DistanceSquared = 1000000.0f;
	
	// Need to export an array so that we get a copy to work on in case new enemies are added by the overlap
	// function while this function is executing.
	TArray<TObjectPtr<AActor>> EnemiesArray = Enemies.Array();
	for (const TObjectPtr<AActor> Enemy : EnemiesArray)
	{
		const float DistSqd = FVector::DistSquared(ActorLocation, Enemy->GetActorLocation());
		if ( DistSqd < DistanceSquared)
		{
			DistanceSquared = DistSqd;
			ClosestLocation = Enemy->GetActorLocation();
		}
	}
	
	return ClosestLocation;
}

void UHomingTargetComponent::OnTargetingSphereOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (const ICharacterBaseInterface* CharacterInterface = Cast<ICharacterBaseInterface>(OtherActor))
	{
		const FGameplayTag Tag = CharacterInterface->GetCharacterTag();
		if (Tag.ToString().Contains("Enemy"))
		{
			Enemies.Add(OtherActor);
		}		
	}

	UpdateTargetingSphereRadius();
}

void UHomingTargetComponent::UpdateTargetingSphereRadius()
{
	if (TargetingRadiusCurveTable)
	{
		const int32 NumberOfEnemies = Enemies.Num();
		if (NumberOfEnemies%5 == 0)
		{
			FString RowName;
			WeaponTag.ToString().Split(TEXT("."), nullptr, &RowName, ESearchCase::IgnoreCase, ESearchDir::FromEnd);
		
			const FRealCurve* Curve = TargetingRadiusCurveTable->FindCurve(*RowName,
																		   FString::Printf(TEXT("Could not find RowName: %s in CurveTable: %s"), *RowName, TEXT("CT_ProjectileHoming")),
																		   true);


			const float Radius = DefaultTargetingRadius * Curve->Eval(NumberOfEnemies, 1.0f);
			SetSphereRadius(Radius);
		}
	}
	else
	{		
		SetSphereRadius(DefaultTargetingRadius);
	}
}

