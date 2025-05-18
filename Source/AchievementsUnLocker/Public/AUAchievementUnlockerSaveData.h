#pragma once

#include <CoreMinimal.h>
#include <GameplayTags.h>

struct FAUAchievementUnlockerSaveData
{
    TArray< FGameplayTag > UnlockedAchievements;
    TMap< FGameplayTag, int > AchievementsProgression;
};

FORCEINLINE FArchive & operator<<( FArchive & archive, FAUAchievementUnlockerSaveData & save_data )
{
    archive << save_data.UnlockedAchievements;
    archive << save_data.AchievementsProgression;
    return archive;
}