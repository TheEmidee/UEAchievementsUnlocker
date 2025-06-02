#include "AUAchievementsUnlockerComponent.h"

#include "AUAchievementsUnlockerSettings.h"
#include "AUAchievementsUnlockerSubsystem.h"

UAUAchievementsUnlockerComponent::UAUAchievementsUnlockerComponent() :
    bUseOnlineSubSystem( false )
{
    PrimaryComponentTick.bCanEverTick = false;
}

void UAUAchievementsUnlockerComponent::EndPlay( const EEndPlayReason::Type end_play_reason )
{
    if ( const auto * gi = GetWorld()->GetGameInstance() )
    {
        if ( auto * system = gi->GetSubsystem< UAUAchievementsUnlockerSubsystem >() )
        {
            system->UnRegisterComponent( this );
        }
    }

    Super::EndPlay( end_play_reason );
}

int UAUAchievementsUnlockerComponent::GetAchievementsCount() const
{
    return AchievementDefinitions.Num();
}

bool UAUAchievementsUnlockerComponent::GetAchievementDefinition( FAUAchievementUnlockerDefinition & definition, FGameplayTag tag ) const
{
    if ( auto * matching_achievement_definition = AchievementDefinitions.FindByPredicate( [ & ]( FAUAchievementUnlockerDefinition * achievement_definition ) {
             return achievement_definition->Tag == tag;
         } ) )
    {
        definition = **matching_achievement_definition;
        return true;
    }

    return false;
}

int UAUAchievementsUnlockerComponent::GetUnlockedAchievementsCount() const
{
    return SaveData.UnlockedAchievements.Num();
}

bool UAUAchievementsUnlockerComponent::IsAchievementUnlocked( FGameplayTag tag ) const
{
    return SaveData.UnlockedAchievements.Contains( tag );
}

int UAUAchievementsUnlockerComponent::GetAchievementProgression( FGameplayTag tag ) const
{
    return SaveData.AchievementsProgression.FindRef( tag );
}

bool UAUAchievementsUnlockerComponent::UnlockAchievement( FGameplayTag tag )
{
    if ( !IsAchievementUnlocked( tag ) )
    {
        SaveData.UnlockedAchievements.AddUnique( tag );
        ReceiveAchievementUnlocked( tag );

        if ( AllAchievementsUnlockedAchievement != nullptr )
        {
            const auto achievement_remaining = GetAchievementsCount() - GetUnlockedAchievementsCount();
            if ( achievement_remaining == 1 )
            {
                UnlockAchievement( AllAchievementsUnlockedAchievement->Tag );
            }
        }

        return true;
    }

    return false;
}

void UAUAchievementsUnlockerComponent::UnlockAchievements( FGameplayTagContainer tags )
{
    for ( auto iterator = tags.CreateConstIterator(); iterator; ++iterator )
    {
        UnlockAchievement( *iterator );
    }
}

void UAUAchievementsUnlockerComponent::IncrementAchievementProgression( FGameplayTag tag, int increment )
{
    SetAchievementProgression( tag, GetAchievementProgression( tag ) + increment );
}

void UAUAchievementsUnlockerComponent::IncrementAchievementsProgression( FGameplayTagContainer tags, int increment )
{
    for ( auto iterator = tags.CreateConstIterator(); iterator; ++iterator )
    {
        IncrementAchievementProgression( *iterator, increment );
    }
}

void UAUAchievementsUnlockerComponent::SetAchievementProgression( FGameplayTag tag, int new_progression )
{
    if ( IsAchievementUnlocked( tag ) )
    {
        return;
    }

    FAUAchievementUnlockerDefinition definition;
    if ( !GetAchievementDefinition( definition, tag ) )
    {
        return;
    }

    new_progression = FMath::Min( new_progression, definition.RequiredProgression );

    SaveData.AchievementsProgression.FindOrAdd( tag ) = new_progression;

    if ( new_progression >= definition.RequiredProgression )
    {
        UnlockAchievement( tag );
        return;
    }

    ReceiveAchievementProgressionUpdated( tag, new_progression );
}

void UAUAchievementsUnlockerComponent::SetAchievementsProgression( FGameplayTagContainer tags, int new_progression )
{
    for ( auto iterator = tags.CreateConstIterator(); iterator; ++iterator )
    {
        SetAchievementProgression( *iterator, new_progression );
    }
}

void UAUAchievementsUnlockerComponent::BeginPlay()
{
    Super::BeginPlay();

    if ( auto * settings = GetDefault< UAUAchievementsUnlockerSettings >() )
    {
        if ( auto * data_table = settings->AchievementsDataTable.LoadSynchronous() )
        {
            data_table->GetAllRows( TEXT( "" ), AchievementDefinitions );

            for ( const auto & achievement : AchievementDefinitions )
            {
                if ( achievement->bUnlockOnAllAchievementsUnlocked )
                {
                    AllAchievementsUnlockedAchievement = achievement;
                    break;
                }
            }
        }

        bUseOnlineSubSystem = settings->bUseOnlineSubsystem;
    }

    if ( const auto * gi = GetWorld()->GetGameInstance() )
    {
        if ( auto * system = gi->GetSubsystem< UAUAchievementsUnlockerSubsystem >() )
        {
            system->RegisterComponent( this );
        }
    }
}

void UAUAchievementsUnlockerComponent::ReceiveAchievementProgressionUpdated_Implementation( FGameplayTag tag, int new_progression )
{
}

void UAUAchievementsUnlockerComponent::ReceiveAchievementUnlocked_Implementation( FGameplayTag tag )
{
}