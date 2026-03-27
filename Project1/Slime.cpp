#include "Slime.h"
#include<iostream>
using namespace std;

Slime::Slime(int level) : Monster(level) {
    name = "Goblin";
    health = level * 30;
    attack = level * 5;

    droptable.addItem(ItemID::HealthPotion, 0.5);
    droptable.addItem(ItemID::AttackBoost, 0.5);
}


void Slime::takeDamage(int damage) {
    health -= damage;


}