#include "SaveLoadManager.h"
#include "Character.h"
#include "ItemFactory.h"
#include <fstream>
#include <iostream>
#include <sstream>

using namespace std;

void SaveLoadManager::Save(Character& player) {
    ofstream file("save.txt");

    if (!file.is_open()) return;

    // ⭐ 1. 장착 해제 (임시)
    auto weapon = player.UnequipWeapon();
    auto armor = player.UnequipArmor();

    // 2. 스탯 저장 (순수 상태)
    file << player.GetName() << "\n";
    file << player.GetLevel() << " "
        << player.GetHealth() << " "
        << player.GetMaxHealth() << " "
        << player.GetAttack() << " "
        << player.GetExperience() << " "
        << player.GetGold() << "\n";

    // 3. 인벤토리 저장
    const auto& inv = player.GetInventory();
    for (const auto& item : inv) {
        file << static_cast<int>(item->GetID()) << " ";
    }
    file << "\n";

    // 4. 장착 아이템 ID 저장
    if (weapon)
        file << static_cast<int>(weapon->GetID()) << "\n";
    else
        file << "0\n";

    if (armor)
        file << static_cast<int>(armor->GetID()) << "\n";
    else
        file << "0\n";

    // ⭐ 5. 다시 장착 (복구)
    if (weapon)
        player.EquipWeapon(std::move(weapon));

    if (armor)
        player.EquipArmor(std::move(armor));

    cout << "저장 완료\n";
}

void SaveLoadManager::Load(Character& player) {
    ifstream file("save.txt");

    if (!file.is_open()) return;

    string name;
    int level, hp, max_hp, atk, exp, gold;

    getline(file, name);
    file >> level >> hp >> max_hp >> atk >> exp >> gold;

    // 초기화
    

    // 스탯 적용
    player.SetLevel(level);
    player.SetHealth(hp);
    player.SetMaxHealth(max_hp);
    player.SetAttack(atk);
    player.SetExperience(exp);
    player.SetGold(gold);

    // 인벤토리
    file.ignore();
    string line;
    getline(file, line);

    stringstream ss(line);
    int id;

    while (ss >> id) {
        auto item = ItemFactory::CreateItem(static_cast<ItemID>(id));
        if (item) {
            player.AddItem(std::move(item));
        }
    }

    // 장착 복원
    int weaponID, armorID;
    file >> weaponID;
    file >> armorID;

    if (weaponID != 0) {
        auto weapon = ItemFactory::CreateItem(static_cast<ItemID>(weaponID));
        player.EquipWeapon(std::move(weapon));
    }

    if (armorID != 0) {
        auto armor = ItemFactory::CreateItem(static_cast<ItemID>(armorID));
        player.EquipArmor(std::move(armor));
    }

    cout << "로드 완료\n";
}