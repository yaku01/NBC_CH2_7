#pragma once
#include <string>

class Character;

class SaveLoadManager {
public:
    void Save(Character& player);
    void Load(Character& player);
};