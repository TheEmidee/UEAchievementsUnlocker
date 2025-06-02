#pragma once

#include "AUAchievementUnlockerDefinition.h"
#include "AUAchievementUnlockerSaveData.h"

#include <Components/ActorComponent.h>
#include <CoreMinimal.h>
#include <GameplayTags.h>

#include "AUAchievementsUnlockerComponent.generated.h"

UCLASS( Blueprintable, BlueprintType, ClassGroup = ( Custom ), meta = ( BlueprintSpawnableComponent ) )
class ACHIEVEMENTSUNLOCKER_API UAUAchievementsUnlockerComponent : public UActorComponent
{
    GENERATED_BODY()

public:
    UAUAchievementsUnlockerComponent();

    const FAUAchievementUnlockerSaveData & GetSaveData() const;
    void SetSaveData( const FAUAchievementUnlockerSaveData & save_data );

    void EndPlay( const EEndPlayReason::Type end_play_reason ) override;

    UFUNCTION( BlueprintPure )
    int GetAchievementsCount() const;

    UFUNCTION( BlueprintPure )
    bool GetAchievementDefinition( UPARAM( ref ) FAUAchievementUnlockerDefinition & definition, FGameplayTag tag ) const;

    UFUNCTION( BlueprintPure )
    int GetUnlockedAchievementsCount() const;

    UFUNCTION( BlueprintPure )
    bool IsAchievementUnlocked( FGameplayTag tag ) const;

    UFUNCTION( BlueprintPure )
    int GetAchievementProgression( FGameplayTag tag ) const;

    UFUNCTION( BlueprintCallable )
    virtual bool UnlockAchievement( FGameplayTag tag );

    UFUNCTION( BlueprintCallable )
    virtual void UnlockAchievements( FGameplayTagContainer tags );

    UFUNCTION( BlueprintCallable )
    virtual void IncrementAchievementProgression( FGameplayTag tag, int increment = 1 );

    UFUNCTION( BlueprintCallable )
    virtual void IncrementAchievementsProgression( FGameplayTagContainer tags, int increment = 1 );

    UFUNCTION( BlueprintCallable )
    virtual void SetAchievementProgression( FGameplayTag tag, int new_progression );

    UFUNCTION( BlueprintCallable )
    virtual void SetAchievementsProgression( FGameplayTagContainer tags, int new_progression );

protected:
    void BeginPlay() override;

    UFUNCTION( BlueprintNativeEvent )
    void ReceiveAchievementUnlocked( FGameplayTag tag );

    UFUNCTION( BlueprintNativeEvent )
    void ReceiveAchievementProgressionUpdated( FGameplayTag tag, int new_progression );

    TArray< FAUAchievementUnlockerDefinition * > AchievementDefinitions;
    FAUAchievementUnlockerDefinition * AllAchievementsUnlockedAchievement;
    bool bUseOnlineSubSystem;
    FAUAchievementUnlockerSaveData SaveData;
};

FORCEINLINE const FAUAchievementUnlockerSaveData & UAUAchievementsUnlockerComponent::GetSaveData() const
{
    return SaveData;
}

FORCEINLINE void UAUAchievementsUnlockerComponent::SetSaveData( const FAUAchievementUnlockerSaveData & save_data )
{
    SaveData = save_data;
}