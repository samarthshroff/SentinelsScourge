// Fill out your copyright notice in the Description page of Project Settings.


#include "Actor/PickupSpawner.h"

#include "VampireSurvivorGameplayTags.h"
#include "AbilitySystem/EnemyAttributeSet.h"
#include "Actor/PickupItem.h"
#include "Character/CharacterBase.h"
#include "Actor/VampireSurvivorEffectActor.h"


// Sets default values
APickupSpawner::APickupSpawner()
{
}

// Called when the game starts or when spawned
void APickupSpawner::BeginPlay()
{
	Super::BeginPlay();
	ACharacterBase::OnCharacterDestroyed.AddDynamic(this, &APickupSpawner::OnCharacterDestroyed);
	
}

void APickupSpawner::OnCharacterDestroyed(const AActor* InActor)
{
	float XP = -1.0f;
	FVector DropLocation = FVector::ZeroVector;
	
	if (const ICharacterBaseInterface* CharacterInterface = Cast<ICharacterBaseInterface>(InActor))
	{
		if (CharacterInterface->TagExactExistsInAbilityComponent(VampireSurvivorGameplayTags::Enemy_Root))
		{
			const UEnemyAttributeSet* AttributeSet = CastChecked<UEnemyAttributeSet>(CharacterInterface->GetAttributeSetComponent());
			XP = AttributeSet->GetXP();
			DropLocation = InActor->GetActorLocation();
		}
	}

	if (XP != -1.0f)
	{
		SpawnPickup(DropLocation, XP);
	}
}

void APickupSpawner::SpawnPickup(const FVector& Location, const float XP)
{
	// TODO - This TMap will be a Data Asset later one.
	const int32 XPLevels[]  = {1,3,10};
	
	EXPPickupType PickupType = EXPPickupType::Blue;
	
	int32 Low = 0;
	int32 High = UE_ARRAY_COUNT(XPLevels) - 1;

	while (Low <= High)
	{
		const int32 Mid = (Low + High) / 2;
		if (XPLevels[Mid] <= XP)
		{
			PickupType = static_cast<EXPPickupType>(Mid);
			Low = Mid + 1;
			continue;
		}
		if (XPLevels[Mid] > XP)
		{
			High = Mid - 1;
			continue;
		}
	}

	const TSubclassOf<APickupItem> PickupClass = XPPickups[PickupType];
	FTransform SpawnTransform;
	SpawnTransform.SetLocation(Location);

	// FActorSpawnParameters SpawnParameters;
	// SpawnParameters.Owner = this;
	// SpawnParameters.bNoFail = true;
	// SpawnParameters.Instigator = GetInstigator();
	// SpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;
	// APickupItem* XPPickupActor = GetWorld()->SpawnActor<APickupItem>(PickupClass, SpawnTransform, SpawnParameters);
	// XPPickupActor->Initialize(XP);
	APickupItem* XPPickupActor = GetWorld()->SpawnActorDeferred<APickupItem>(PickupClass, SpawnTransform, this, GetInstigator(),  ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn);
	if (XPPickupActor != nullptr)
	{
		XPPickupActor->Initialize(XP);
		XPPickupActor->FinishSpawning(SpawnTransform);
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Could not spawn pick up actor."));
	}
	
	
}


