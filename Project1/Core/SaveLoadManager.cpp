#include "SaveLoadManager.h"
#include "Character.h"
#include "ItemFactory.h"
#include <fstream>
#include <iostream>
#include <sstream>
 
using namespace std;

void SaveLoadManager::Save(Character& player) {
    // 1. 기존 파일 읽기
    ifstream infile("Save/save.txt");
    stringstream buffer;
    string line;
    bool skip = false;

    while (getline(infile, line)) {
        if (line == "[PLAYER]") {
            string name_line;
            getline(infile, name_line);

            if (name_line == player.GetName()) {
                // 같은 이름 블록 스킵
                skip = true;
                // stats + inventory + weapon + armor 읽고 무시
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
        else if (!skip) {
            buffer << line << "\n";
        }
        else {
            skip = false; // 스킵 후 다시 정상 읽기
        }
    }
    infile.close();

    // 2. 파일 다시 열고 기존 내용 + 새 캐릭터 블록 저장
    ofstream outfile("Save/save.txt");
    outfile << buffer.str();

    // 3. 새 블록 추가
    outfile << "[PLAYER]\n";
    outfile << player.GetName() << "\n";
    outfile << player.GetLevel() << " "
        << player.GetHealth() << " "
        << player.GetMaxHealth() << " "
        << player.GetAttack() << " "
        << player.GetExperience() << " "
        << player.GetGold() << "\n";

    // 인벤토리
    const auto& inv = player.GetInventory();
    for (const auto& item : inv) {
        outfile << static_cast<int>(item->GetID()) << " ";
    }
    outfile << "\n";

    // 장비
    outfile << (player.GetEquippedWeapon() ? static_cast<int>(player.GetEquippedWeapon()->GetID()) : 0) << "\n";
    outfile << (player.GetEquippedArmor() ? static_cast<int>(player.GetEquippedArmor()->GetID()) : 0) << "\n";

}

bool SaveLoadManager::Load(Character& player, const std::string& targetName) {
    std::ifstream file("Save/save.txt");
    if (!file.is_open()) return false;

    std::string line;

    while (std::getline(file, line)) {
        if (line == "[PLAYER]") {

            std::string name;
            std::getline(file, name);

            // X 다른 캐릭터면 스킵
            if (name != targetName) {
                std::getline(file, line); // stats
                std::getline(file, line); // inventory
                std::getline(file, line); // weapon
                std::getline(file, line); // armor
                continue;
            }

            // * 찾았으면 초기화
            player.Reset();
            player.SetName(name);

            int level, hp, max_hp, atk, exp, gold;
            file >> level >> hp >> max_hp >> atk >> exp >> gold;

            player.SetLevel(level);
            player.SetHealth(hp);
            player.SetMaxHealth(max_hp);
            player.SetAttack(atk);
            player.SetExperience(exp);
            player.SetGold(gold);

            file.ignore(); // 줄바꿈 제거

            // * 인벤토리
            std::getline(file, line);
            std::stringstream ss(line);
            int id;

            while (ss >> id) {
                auto item = ItemFactory::CreateItem(static_cast<ItemID>(id));
                if (item) {
                    player.AddItem(std::move(item));
                }
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

            return true;
        }
    }

    return false;
}
