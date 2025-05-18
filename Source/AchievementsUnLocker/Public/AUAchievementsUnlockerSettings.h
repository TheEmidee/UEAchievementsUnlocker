#pragma once

#include <CoreMinimal.h>
#include <Engine/DeveloperSettings.h>

#include "AUAchievementsUnlockerSettings.generated.h"

UCLASS( config = Game, defaultconfig, meta = ( DisplayName = "Achievements Unlocker" ) )
class ACHIEVEMENTSUNLOCKER_API UAUAchievementsUnlockerSettings final : public UDeveloperSettings
{
    GENERATED_BODY()

public:
    UPROPERTY( EditAnywhere, config, meta = ( RowType = "AUAchievementUnlockerDefinition" ) )
    TSoftObjectPtr< UDataTable > AchievementsDataTable;

    // Set to true to have the components attached to the player controllers use the OnlineSubsystem API to update the achievements on the platform backend
    UPROPERTY( EditAnywhere, config )
    bool bUseOnlineSubsystem = false;
};
