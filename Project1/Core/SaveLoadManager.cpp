#include "SaveLoadManager.h"
#include "Character.h"
#include "ItemFactory.h"
#include "Items/Consumable/ConsumableItem.h"
#include <fstream>
#include <iostream>
#include <sstream>

using namespace std;

void SaveLoadManager::Save(Character& player) {

    int saved_health = player.GetHealth();
    auto weapon = player.UnequipWeapon();
    auto armor = player.UnequipArmor();


    // 1. 기존 파일 읽기
    ifstream infile("Save/save.txt");

    stringstream buffer;
    string line;

    while (getline(infile, line)) {
        if (line == "[PLAYER]") {
            string name_line;
            getline(infile, name_line);

            if (name_line == player.GetName()) {
                // 같은 이름 블록 스킵
                for (int i = 0; i < 4; ++i) getline(infile, line);
                continue;
            }
            else {
                buffer << "[PLAYER]\n" << name_line << "\n";
                for (int i = 0; i < 4; ++i) {
                    getline(infile, line);
                    buffer << line << "\n";
                }
            }
        }
    }
    infile.close();


    // 2. 파일 다시 열고 기존 내용 + 새 캐릭터 블록 저장
    ofstream outfile("Save/save.txt");

    outfile << buffer.str();


    // ⭐ 새 데이터 저장
    outfile << "[PLAYER]\n";
    outfile << player.GetName() << "\n";

    outfile << player.GetLevel() << " "
        << saved_health << " "
        << player.GetMaxHealth() << " "
        << player.GetAttack() << " "
        << player.GetExperience() << " "
        << player.GetGold() << "\n";

    // ⭐ 인벤토리 (ID:count)
    const auto& inv = player.GetInventory();
    for (const auto& item : inv) {
        if (item->GetType() == ItemType::Consumable) {
            auto* consumable = dynamic_cast<ConsumableItem*>(item.get());
            if (consumable) {
                outfile << static_cast<int>(item->GetID())
                    << ":" << consumable->GetCount() << " ";
            }
        }
        else {
            outfile << static_cast<int>(item->GetID()) << ":1 ";
        }
    }
    outfile << "\n";

    // ⭐ 장비
    outfile << (weapon
        ? static_cast<int>(weapon->GetID())
        : 0) << "\n";

    outfile << (armor
        ? static_cast<int>(armor->GetID())
        : 0) << "\n";
    if (weapon) player.EquipWeapon(std::move(weapon));
    if (armor) player.EquipArmor(std::move(armor));
}

bool SaveLoadManager::Load(Character& player, const std::string& targetName) {

    std::ifstream file("Save/save.txt");
    if (!file.is_open()) return false;

    string line;

    while (getline(file, line)) {
        if (line == "[PLAYER]") {

            string name;
            getline(file, name);


            // 다른 캐릭터면 스킵
            if (name != targetName) {
                for (int i = 0; i < 4; ++i) getline(file, line);
                continue;
            }

            // * 찾았으면 초기화

            player.Reset();
            player.SetName(name);

            int level, hp, max_hp, atk, exp, gold;
            file >> level >> hp >> max_hp >> atk >> exp >> gold;

            player.SetLevel(level);
            player.SetMaxHealth(max_hp);
            player.SetAttack(atk);
            player.SetExperience(exp);
            player.SetGold(gold);

            file.ignore(); // 줄바꿈 제거

            // ⭐ 인벤토리 (ID:count 파싱)
            getline(file, line);
            stringstream ss(line);
            string token;

            while (ss >> token) {
                size_t pos = token.find(':');

                int id = stoi(token.substr(0, pos));
                int count = stoi(token.substr(pos + 1));

                auto item = ItemFactory::CreateItem(static_cast<ItemID>(id));
                if (!item) continue;

                if (item->GetType() == ItemType::Consumable) {
                    auto* consumable = dynamic_cast<ConsumableItem*>(item.get());
                    if (consumable) {
                        consumable->AddCount(count - 1); // 기본 1 보정
                    }
                }

                player.AddItem(std::move(item));
            }

            // * 장비
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

            player.SetHealth(std::min(hp,player.GetMaxHealth()));

            return true;
        }
    }

    return false;
}