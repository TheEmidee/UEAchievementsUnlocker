#pragma once

#include <Modules/ModuleManager.h>

class FAchievementsUnLockerModule final : public IModuleInterface
{
public:
    void StartupModule() override;
    void ShutdownModule() override;
};
