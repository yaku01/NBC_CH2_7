#pragma once
#include"DropTable.h"
#include<string>
#include<vector>
#include<random>

using namespace std;


class Monster {
public:
	Monster(int level) : level(level), health(1), attack(1){}
    virtual ~Monster(){}
    virtual void takeDamage(int damage) = 0;
    virtual vector<ItemID> getDropItems() {
        return droptable.drop();
    }

    bool IsDead() const { return health <= 0; };

    //getter 함수

    string getName() const {
        return name;
    }

    int getHealth() const {
        return health;
    }

    int getAttack() const {
        return attack;
    }

    int getLevel() const {
        return level;
    }

    // setter 함수

    void setName(const string &name) {
        this->name = name;
    }

    void setHealth(int health) {
        this->health = health;
    }

    void setAttack(int attack) {
        this->attack = attack;
    }

    void setLevel(int level) {
        this->level = level;
    }



protected:
    string name;
    int health;
    int attack;
    int level;
    DropTable droptable;

};

