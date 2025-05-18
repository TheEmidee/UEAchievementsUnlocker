#include "AUAchievementsUnlockerSubsystem.h"

void UAUAchievementsUnlockerSubsystem::RegisterComponent( UAUAchievementsUnlockerComponent * component )
{
    RegisteredComponents.AddUnique( component );
}

void UAUAchievementsUnlockerSubsystem::UnRegisterComponent( UAUAchievementsUnlockerComponent * component )
{
    RegisteredComponents.Remove( component );
}

UAUAchievementsUnlockerComponent * UAUAchievementsUnlockerSubsystem::GetComponentFromPlayerController( APlayerController * player_controller ) const
{
    if ( auto * component = RegisteredComponents.FindByPredicate( [ player_controller ]( auto registered_component ) {
             return registered_component->GetOwner() == player_controller;
         } ) )
    {
        return *component;
    }

    return nullptr;
}