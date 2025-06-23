#pragma once

#include <CoreMinimal.h>
#include <GameplayTags.h>

struct FAUAchievementUnlockerSaveData
{
    void Reset();

    TArray< FGameplayTag > UnlockedAchievements;
    TMap< FGameplayTag, int > AchievementsProgression;
};

FORCEINLINE FArchive & operator<<( FArchive & archive, FAUAchievementUnlockerSaveData & save_data )
{
    archive << save_data.UnlockedAchievements;
    archive << save_data.AchievementsProgression;
    return archive;
}

FORCEINLINE void FAUAchievementUnlockerSaveData::Reset()
{
    UnlockedAchievements.Empty();
    AchievementsProgression.Empty();
}