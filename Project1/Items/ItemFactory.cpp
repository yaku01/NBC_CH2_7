#include "ItemFactory.h"
#include "Consumable/HealthPotion.h"
#include "Consumable/AttackBoost.h"
#include "Equippable/Sword.h"
#include "Equippable/Armor.h"

// 아이템 생성 함수를 등록하는 맵
std::map<ItemID, std::function<std::unique_ptr<IItem>()>> ItemFactory::item_creators;

// 아이템 생성 함수를 등록
// 프로그램 시작 시 ItemFactory::Initialize(); 를 호출하여 아이템 생성 함수를 등록해야 합니다.
void ItemFactory::Initialize() 
{
	item_creators[ItemID::HealthPotion] = []() { return std::make_unique<HealthPotion>(); };
	item_creators[ItemID::AttackBoost] = []() { return std::make_unique<AttackBoost>(); };
	item_creators[ItemID::WoodSword] = []() { return std::make_unique<Sword>("Wood Sword", ItemID::WoodSword, "공격력이 5 증가합니다.", 5); }; 
	item_creators[ItemID::Sword] = []() { return std::make_unique<Sword>("Sword", ItemID::Sword, "공격력이 15 증가합니다.", 15); };
	item_creators[ItemID::LeatherArmor] = []() { return std::make_unique<Armor>("Leather Armor", ItemID::LeatherArmor, "최대 체력이 20 증가합니다.", 20); };
	item_creators[ItemID::Armor] = []() { return std::make_unique<Armor>("Armor", ItemID::Armor, "최대 체력이 50 증가합니다.", 50); };
}
 
// 아이템 생성 함수
std::unique_ptr<IItem> ItemFactory::CreateItem(ItemID id) 
{
	auto it = item_creators.find(id);
	if (it != item_creators.end()) 
	{
		return it->second(); // 등록된 생성 함수를 호출하여 아이템 생성
	}
	return nullptr; // 등록되지 않은 ID인 경우 nullptr 반환
}
