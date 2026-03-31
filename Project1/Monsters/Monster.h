#pragma once
#include"DropTable.h"
#include<string>
#include<vector>
#include<random>

using namespace std;


class Monster {
public:
	Monster(int level) : level(level), health(1), attack(1), maxhealth(1),is_active(true){}
    virtual ~Monster(){}
    virtual void TakeDamage(int damage) = 0;
    vector<ItemID> GetDropItems() {
        return droptable.drop();
    }
    virtual string GetAsciiArtPath() const = 0;
    

    bool IsDead() const { return health <= 0; };
    bool IsActive() const { return is_active; }

    //getter 함수

    string GetName() const {
        return name;
    }

    int GetHealth() const {
        return health;
    }

    int GetAttack() const {
        return attack;
    }

    int GetLevel() const {
        return level;
    }

    int GetMaxHealth() const {
        return maxhealth;
    }

    // setter 함수

    void SetActive(bool active) {
        this->is_active = active;
    };

    void SetName(const string &name) {
        this->name = name;
    }

    void SetHealth(int health) {
        this->health = health;
    }

    void SetAttack(int attack) {
        this->attack = attack;
    }

    void SetLevel(int level) {
        this->level = level;
    }



protected:
    string name;
    int health;
    int attack;
    int level;
    DropTable droptable;
    bool is_active;
    int maxhealth;
    string file_path;
};

