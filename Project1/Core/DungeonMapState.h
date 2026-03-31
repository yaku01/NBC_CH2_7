#pragma once
#include <string>

namespace DungeonMapState
{
    void ResetToFirstMap();
    void SetRandomBattleMap();
    const std::string& GetCurrentMapPath();
} 
