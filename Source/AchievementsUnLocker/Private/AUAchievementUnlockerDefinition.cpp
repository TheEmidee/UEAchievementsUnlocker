#include "AUAchievementUnlockerDefinition.h"

FAUAchievementUnlockerDefinition::FAUAchievementUnlockerDefinition() :
    bUnlockOnAllAchievementsUnlocked( false )
{}

bool FAUAchievementUnlockerDefinition::IsValid() const
{
    return Tag.IsValid();
}