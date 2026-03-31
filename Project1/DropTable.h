#pragma once
#include "Item.h"
#include "Common/common.h"
#include <vector>
#include <string>

using namespace std;

struct DropItem {
    ItemID item_id;
    double probability;
};

class DropTable {
private:
    vector<DropItem> items;

public:
    DropTable() {}

    void addItem(ItemID id, double prob) {
        items.push_back({ id, prob });
    }

    vector<ItemID> drop() {
        vector<ItemID> droppedItems;

        for (const auto& item : items) {
            if (RandomUtil::IsSuccess(item.probability)) {
                droppedItems.push_back(item.item_id);
            }
        }
         
        return droppedItems;
    }
};
