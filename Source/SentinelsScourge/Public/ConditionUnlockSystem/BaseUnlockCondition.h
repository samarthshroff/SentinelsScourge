// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseUnlockCondition.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnConditionProgressUpdated, float, NewProgressRatio);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnConditionMet, class UBaseUnlockCondition *, MetCondition);

/**
 * Base class for all unlock conditions.
 * Inherit from this to create specific unlock conditions (e.g., KillXEnemies, SurviveYMinutes).
 */
UCLASS() // Blueprintable, BlueprintType, EditInlineNew, DefaultToInstanced)
class SENTINELSSCOURGE_API UBaseUnlockCondition : public UObject
{
    GENERATED_BODY()

public:
    // Tracks current progress (0.0 to 1.0)
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Condition")
    float CurrentProgressRatio;

    // Event delegates
    UPROPERTY(BlueprintAssignable, Category = "Condition")
    FOnConditionProgressUpdated OnConditionProgressUpdated;

    UPROPERTY(BlueprintAssignable, Category = "Condition")
    FOnConditionMet OnConditionMet;

protected:
    UPROPERTY(BlueprintReadOnly, Category = "Condition")
    bool bIsConditionMet;

    // Called when the condition is initialized (e.g., when player starts game/accesses unlock menu)
    // UFUNCTION(BlueprintNativeEvent, Category = "Condition")
    virtual void InitializeCondition(AActor *OwningActor); // OwningActor could be PlayerState or GameState

    // // Called when the condition needs to be checked
    // // Specific conditions will override this to listen to relevant game events
    // UFUNCTION(BlueprintCallable, Category = "Condition")
    // virtual void CheckCondition(AActor* OwningActor);
    //
    // // Call this when progress changes
    // UFUNCTION(BlueprintCallable, Category = "Condition")
    // void UpdateProgress(float NewProgress); // NewProgress is 0.0-1.0
    //
    // // Call this when condition is met
    // UFUNCTION(BlueprintCallable, Category = "Condition")
    // void MarkConditionMet();
};
