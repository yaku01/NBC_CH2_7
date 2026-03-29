#pragma once
#include "BaseScene.h"
#include "Items/Item.h"
#include <memory>
#include <vector>

class ShopUI;
class ItemConfirmUI;

enum class ShopState { Buy, Sell };
enum class ShopInputState { Normal, Confirm };

class ShopScene : public BaseScene
{
public:
	ShopScene();
	~ShopScene();

	void Init() override;
	void SetMenu() override;
	void ProcessEvent(const Event& e) override;
	void Update(float delta_time) override;
	void Render() override;
	void Release() override;

private:
	ShopState current_state = ShopState::Buy;
	ShopInputState input_state = ShopInputState::Normal;
	std::vector<ItemID> shop_items;
	size_t selected_index = 0;
	std::unique_ptr<ShopUI> shop_ui;
	std::unique_ptr<ItemConfirmUI> popup_ui;

	void ReadItemList();
	void ProcessNormalMode(const Event& e);
	void ProcessItemConfirm(const Event& e);
	void TradeItem();
};

