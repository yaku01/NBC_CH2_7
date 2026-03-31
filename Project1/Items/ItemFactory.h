#pragma once
#include "Item.h"

#include <memory>
#include <map>
#include <functional>

class ItemFactory
{
private:
	// 아이템 ID와 생성 함수를 매핑하는 맵
	static std::map<ItemID, std::function<std::unique_ptr<IItem>()>> item_creators;

public:
	// 아이템 생성 함수를 등록 
	static void Initialize();

	// 아이템 생성 함수
	static std::unique_ptr<IItem> CreateItem(ItemID id);
};
