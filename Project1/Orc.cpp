#include "Orc.h"
#include<iostream>
using namespace std;

Orc::Orc(int level) : Monster(level) {
    name = "Orc";
    health = level * 150;
    attack = level * 17;

    droptable.addItem(ItemID::HealthPotion, 0.5);
    droptable.addItem(ItemID::AttackBoost, 0.5);
}



void Orc::takeDamage(int damage) {

    health -= damage;

}