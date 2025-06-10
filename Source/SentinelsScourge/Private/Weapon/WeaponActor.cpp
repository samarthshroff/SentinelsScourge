// Copyright (c) Samarth Shroff. All Rights Reserved.
// This work is protected under applicable copyright laws in perpetuity.
// Licensed under the CC BY-NC-ND 4.0 License. See LICENSE file for details.

#include "Weapon/WeaponActor.h"

// Sets default values
AWeaponActor::AWeaponActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	//PrimaryActorTick.bCanEverTick = true;
	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("SkeletalMesh"));
	RootComponent = StaticMesh;
}

// Called when the game starts or when spawned
void AWeaponActor::BeginPlay()
{
	Super::BeginPlay();	
}

// // Called every frame
// void AWeaponActor::Tick(float DeltaTime)
// {
// 	Super::Tick(DeltaTime);
//
// }

void AWeaponActor::SetStaticMesh(TObjectPtr<UStaticMesh> Mesh) const
{
	StaticMesh->SetStaticMesh(Mesh);
}

