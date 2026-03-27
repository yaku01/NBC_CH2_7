#pragma once
#include "Item.h"
#include <vector>
#include <string>
#include <random>

using namespace std;

struct DropItem {
    ItemID item_id;
    double probability;
};

class DropTable {
private:
    vector<DropItem> items;
    mt19937 rng;

public:
    DropTable() : rng(random_device{}()) {}

    void addItem(const ItemID& id, double prob) {
        items.push_back({ id, prob });
    }

    vector<ItemID> drop() {
        vector<ItemID> droppedItems;

        uniform_real_distribution<double> dist(0.0, 1.0);  // 0.0 ~ 1.0 (확률)

        for (const auto& item : items) {
            double randomValue = dist(rng);  // 아이템 마다 난수 생성

            if (randomValue < item.probability) {
                droppedItems.push_back(item.item_id);
            }
        }

        return droppedItems;
    }
};