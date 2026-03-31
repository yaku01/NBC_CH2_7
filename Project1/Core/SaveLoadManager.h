#pragma once
#include <string>

class Character;

class SaveLoadManager {
public:
    static void Save(Character& player);
    static bool Load(Character& player, const std::string& name);
}; 
