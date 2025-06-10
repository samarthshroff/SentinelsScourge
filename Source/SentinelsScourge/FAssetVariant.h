// Copyright (c) Samarth Shroff. All Rights Reserved.
// This work is protected under applicable copyright laws in perpetuity.
// Licensed under the CC BY-NC-ND 4.0 License. See LICENSE file for details.

#pragma once
#include "FAssetVariant.generated.h"

class UNiagaraSystem;

UENUM(BlueprintType)
enum class EAssetVariant : uint8
{
	None UMETA(DisplayName = "None"),
	NiagaraSystem UMETA(DisplayName = "NiagaraSystem"),
	StaticMesh UMETA(DisplayName = "StaticMesh")
};

USTRUCT(BlueprintType)
struct FAssetVariant
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mesh Variant")
	EAssetVariant Variant;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (EditCondition = "Variant == EAssetVariant::NiagaraSystem"))
	TSoftObjectPtr<UNiagaraSystem> NiagaraSystemClass;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (EditCondition = "Variant == EAssetVariant::StaticMesh"))
	TSoftObjectPtr<UStaticMesh> StaticMesh;

	void SetNiagaraSystemClass(TSoftObjectPtr<UNiagaraSystem> InNiagaraSystemClass);

	void SetStaticMesh(TSoftObjectPtr<UStaticMesh> InStaticMesh);

	TSoftObjectPtr<UObject> GetAsset() const;

	FAssetVariant() = default;

	FAssetVariant(const FAssetVariant& Other):
	Variant(Other.Variant),
	NiagaraSystemClass(Other.NiagaraSystemClass),
	StaticMesh(Other.StaticMesh)
	{}

	FAssetVariant& operator=(const FAssetVariant& Other)
	{
		if (this != &Other)
		{
			Variant = Other.Variant;
			NiagaraSystemClass = Other.NiagaraSystemClass;
			StaticMesh = Other.StaticMesh;
		}
		return *this;
	}

	FAssetVariant(FAssetVariant&& Other) noexcept:
	Variant(MoveTemp(Other.Variant)),
	NiagaraSystemClass (MoveTemp(Other.NiagaraSystemClass)),
	StaticMesh (MoveTemp(Other.StaticMesh))
	{
		
	}

	FAssetVariant& operator=(FAssetVariant&& Other) noexcept
	{
		if (this != &Other)
		{
			Variant = Other.Variant;
			NiagaraSystemClass = MoveTemp(Other.NiagaraSystemClass);
			StaticMesh = MoveTemp(Other.StaticMesh);
		}
		return *this;
	}
};
