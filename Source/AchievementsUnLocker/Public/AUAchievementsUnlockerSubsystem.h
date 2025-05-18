#pragma once

#include "AUAchievementsUnlockerComponent.h"

#include <CoreMinimal.h>
#include <Subsystems/GameInstanceSubsystem.h>

#include "AUAchievementsUnlockerSubsystem.generated.h"

UCLASS()
class ACHIEVEMENTSUNLOCKER_API UAUAchievementsUnlockerSubsystem final : public UGameInstanceSubsystem
{
    GENERATED_BODY()

public:
    void RegisterComponent( UAUAchievementsUnlockerComponent * component );
    void UnRegisterComponent( UAUAchievementsUnlockerComponent * component );

    UFUNCTION( BlueprintPure )
    UAUAchievementsUnlockerComponent * GetComponentFromPlayerController( APlayerController * player_controller ) const;

private:
    UPROPERTY()
    TArray< TObjectPtr< UAUAchievementsUnlockerComponent > > RegisteredComponents;
};
