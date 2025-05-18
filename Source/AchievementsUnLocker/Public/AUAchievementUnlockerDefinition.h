#pragma once

#include <CoreMinimal.h>
#include <GameplayTagContainer.h>

#include "AUAchievementUnlockerDefinition.generated.h"

USTRUCT( BlueprintType )
struct FAUAchievementUnlockerDefinition final : public FTableRowBase
{
    GENERATED_USTRUCT_BODY()

    FAUAchievementUnlockerDefinition() = default;

    UPROPERTY( EditDefaultsOnly, BlueprintReadOnly )
    FGameplayTag Tag;

    // The id of the achievement when you want to use the OnlineSubsystem
    UPROPERTY( EditDefaultsOnly, BlueprintReadOnly )
    FString Id;

    UPROPERTY( EditDefaultsOnly, BlueprintReadOnly )
    FText Name;

    UPROPERTY( EditDefaultsOnly, BlueprintReadOnly, meta = ( MultiLine = true ) )
    FText Description;

    UPROPERTY( EditDefaultsOnly, BlueprintReadOnly )
    int RequiredProgression = INDEX_NONE;

    UPROPERTY( EditDefaultsOnly, BlueprintReadOnly )
    TSoftObjectPtr< UTexture2D > UnlockedTexture;

    UPROPERTY( EditDefaultsOnly, BlueprintReadOnly )
    TSoftObjectPtr< UTexture2D > LockedTexture;
};