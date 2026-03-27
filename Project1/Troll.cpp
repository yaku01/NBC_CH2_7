#include "Troll.h"
#include<iostream>
using namespace std;

Troll::Troll(int level) : Monster(level) {
    name = "Goblin";
    health = level * 80;
    attack = level * 10;

    droptable.addItem(ItemID::HealthPotion, 0.5);
    droptable.addItem(ItemID::AttackBoost, 0.5);
}



void Troll::takeDamage(int damage) {

    health -= damage;

}