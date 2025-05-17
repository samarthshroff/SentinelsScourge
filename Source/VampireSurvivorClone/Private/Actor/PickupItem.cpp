// Fill out your copyright notice in the Description page of Project Settings.


#include "Actor/PickupItem.h"

#include "VampireSurvivorCloneGameMode.h"
#include "VampireSurvivorGameplayTags.h"
#include "Character/CharacterBaseInterface.h"
#include "Components/BoxComponent.h"


// Sets default values
APickupItem::APickupItem()
{
	BoxComp = CreateDefaultSubobject<UBoxComponent>("Box");
	SetRootComponent(BoxComp);

	BoxComp->SetGenerateOverlapEvents(true);
	BoxComp->SetCollisionObjectType(ECC_PickupItemsChannel);
	BoxComp->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	BoxComp->SetCollisionResponseToAllChannels(ECR_Ignore);
	BoxComp->SetCollisionResponseToChannel(ECC_PlayerCharacterChannel, ECR_Overlap);

	BoxComp->OnComponentBeginOverlap.AddDynamic(this, &APickupItem::OnBoxOverlap);
	BoxComp->SetHiddenInGame(true);

	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>("StaticMesh");
	StaticMesh->SetupAttachment(RootComponent);
	StaticMesh->SetGenerateOverlapEvents(false);
	StaticMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	StaticMesh->SetCollisionResponseToAllChannels(ECR_Ignore);
}

// Called when the game starts or when spawned
void APickupItem::BeginPlay()
{
	Super::BeginPlay();
	
}

void APickupItem::Initialize(const float InXP)
{
	// // TODO - Maybe I can render then on a different layer altogether so that player can overlap but enemies won't
	SetByCallerValues.Reset();
	SetByCallerValues.Add(VampireSurvivorGameplayTags::Effect_Modifier_XP, InXP);	
}

void APickupItem::OnBoxOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
	bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor == nullptr) return;
	if (const ICharacterBaseInterface* CharacterBaseInterface = Cast<ICharacterBaseInterface>(OtherActor))
	{
		if (CharacterBaseInterface->TagExactExistsInAbilityComponent(VampireSurvivorGameplayTags::Hero_Root))
		{	
			OnBeginOverlap(OtherActor);
			BoxComp->SetCollisionEnabled(ECollisionEnabled::Type::NoCollision);
			Destroy();
		}
	}
}






