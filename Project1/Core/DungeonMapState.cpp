#include "DungeonMapState.h"
#include <vector>
#include <random>
#include <ctime>
 
namespace
{
    std::string currentMapPath = "Resource/dungeon_map_1.txt";

    std::vector<std::string> randomMaps =
    {
        "Resource/dungeon_map_2.txt",
        "Resource/dungeon_map_3.txt",
        "Resource/dungeon_map_4.txt"
    };

    std::mt19937& GetRng()
    {
        static std::mt19937 rng(static_cast<unsigned int>(std::time(nullptr)));
        return rng;
    }
}

namespace DungeonMapState
{
    void ResetToFirstMap()
    {
        currentMapPath = "Resource/dungeon_map_1.txt";
    }

    void SetRandomBattleMap()
    {
        if (randomMaps.empty()) {
            return;
        }

        static std::string lastMapPath = "";
        std::uniform_int_distribution<int> dist(0, static_cast<int>(randomMaps.size()) - 1);

        std::string newMap;
        do
        {
            newMap = randomMaps[dist(GetRng())];
        } while (randomMaps.size() > 1 && newMap == lastMapPath);

        currentMapPath = newMap;
        lastMapPath = newMap;
    }

    const std::string& GetCurrentMapPath()
    {
        return currentMapPath;
    }
}
