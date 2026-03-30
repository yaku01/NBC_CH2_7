#include "ShopScene.h"
#include "UI/UIManager.h"
#include "UI/GameUI.h"
#include "Core/RenderSystem.h"
#include "Characters/Character.h"
#include "Core/ItemDataBase.h"
#include "Items/ItemFactory.h"
#include "Core/ResourceManager.h"

ShopScene::ShopScene() = default;
ShopScene::~ShopScene() = default;

void ShopScene::Init()
{
	current_state = ShopState::Buy;
	input_state = ShopInputState::Normal;
	selected_index = 0;

	LoadItemList(shop_path);

	// -----------
	// 배경
	auto bg = std::make_unique<AsciiUI>(0, 0);
	bg->LoadAsciiArt("Resource/Shop_BackGround.txt");
	scene_uis.push_back(std::move(bg));


	// 상점 ui
	int start_x = 3;
	int start_y = 3;
	int width = 50;
	int height = 20;
	shop_ui = std::make_unique<ShopUI>(start_x, start_y, width, height);
	shop_ui->SetMode(true, &shop_items);


	// 확인 팝업 ui
	int w = RenderSystem::GetInstance().GetScreenWidth();
	int h = RenderSystem::GetInstance().GetScreenHeight();

	start_x = static_cast<int>(w * 0.15f);
	start_y = static_cast<int>(h * 0.15f);
	width = static_cast<int>(w * 0.4f);
	height = 8;
	popup_ui = std::make_unique<ItemConfirmUI>(start_x, start_y, width, height);

	SetMenu();
}

void ShopScene::SetMenu()
{
	UIManager::GetInstance().ClearContent(UIType::Menu);

	switch (current_state) {
	case ShopState::Buy:
		UIManager::GetInstance().AddContent(UIType::Menu, "1~9. 아이템 구매   0. 마을로 돌아가기  Tab : 판매/구매 전환");
		UIManager::GetInstance().AddContent(UIType::Menu, "구매할 아이템의 번호를 입력하세요: ");
		break;

	case ShopState::Sell:
		UIManager::GetInstance().AddContent(UIType::Menu, "1~9. 아이템 구매   0. 마을로 돌아가기  Tab : 판매/구매 전환");
		UIManager::GetInstance().AddContent(UIType::Menu, "판매할 아이템의 번호를 입력하세요: ");
		break;
	}
}

void ShopScene::ProcessEvent(const Event& e)
{
	if (e.type != EventType::KeyDown) {
		return;
	}

	if (input_state == ShopInputState::Normal) {
		ProcessNormalMode(e);
	}
	else {
		ProcessItemConfirm(e);
	}

	SetMenu();
}

void ShopScene::Update(float delta_time)
{
}

void ShopScene::Render()
{
	BaseScene::Render();

	if (shop_ui) {
		shop_ui->Render();
	}
	if (popup_ui) {
		popup_ui->Render();
	}
}

void ShopScene::Release()
{
	shop_items.clear();
	BaseScene::Release();
}

void ShopScene::SetSceneData(const std::string& data)
{
	shop_path = data;
}

void ShopScene::LoadItemList(const std::string& path)
{
	shop_items.clear();

	auto res = ResourceManager::GetInstance().GetResource(path);

	if (!res.has_value()) {
		UIManager::GetInstance().AddContent(UIType::Log, "[에러] 상점 파일을 찾을 수 없습니다");
		return;
	}

	const auto& data = res->get();
	for (const auto& s : data) {
		if (s.empty()) {
			continue;
		}

		int id = std::stoi(s);
		shop_items.push_back(static_cast<ItemID>(id));
	}
}

void ShopScene::ProcessNormalMode(const Event& e)
{
	switch (e.key_code) {

		// 9 = 탭키, 구매/판매 모드 전환
	case 9:
	{
		int next = (static_cast<int>(current_state) + 1) % 2;
		current_state = static_cast<ShopState>(next);

		bool is_buy_mode = (current_state == ShopState::Buy);
		shop_ui->SetMode(is_buy_mode, &shop_items);

		SetMenu();
		break;
	}

	case '0':
		PopScene();
		break;
		
	case 'q':
	case 'Q':
		shop_ui->PrevPage();
		break;

	case 'e':
	case 'E':
	{
		int total_items = (current_state == ShopState::Buy) ?
			static_cast<int>(shop_items.size()) :
			static_cast<int>(Character::GetInstance().GetInventory().size());
		shop_ui->NextPage(total_items);
		break;
	}

	default:
	{
		int idx = e.key_code - '0';
		if (idx < 1 || idx > 9) {
			return;
		}

		size_t target_idx = static_cast<size_t>
			(shop_ui->GetCurrentPage() * shop_ui->GetItemsPerPage() + (idx - 1));

		bool is_valid = false;
		const auto& inventory = Character::GetInstance().GetInventory();

		// 구매상태일땐 shop_items 로 유효 체크
		// 판매상태일땐 inventory 에서 유효 체크
		if (current_state == ShopState::Buy) {
			is_valid = (target_idx < shop_items.size());
		}
		else {
			is_valid = (target_idx < inventory.size());
		}

		if (is_valid) {
			selected_index = target_idx;
			input_state = ShopInputState::Confirm;

			std::string action = (current_state == ShopState::Buy) ? "구매" : "판매";
			popup_ui->SetActionText(action + "하시겠습니까?");

			if (current_state == ShopState::Buy) {
				popup_ui->SetTarget(shop_items[target_idx]);
			}
			else {
				popup_ui->SetTarget(inventory[target_idx]->GetID());
			}

			SetMenu();
		}
		break;
	}	// default 끝

	}
}

void ShopScene::ProcessItemConfirm(const Event& e)
{
	switch (e.key_code) {
	case 'y':
	case 'Y':
		TradeItem();
		[[fallthrough]];

	case 'n':
	case 'N':
		popup_ui->SetTarget(ItemID::None);
		input_state = ShopInputState::Normal;
		SetMenu();
		break;
	}
}

void ShopScene::TradeItem()
{
	Character& player = Character::GetInstance();

	if (current_state == ShopState::Buy) {
		ItemID id = shop_items[selected_index];
		const ItemData& data = ItemDataBase::GetData(id);

		if (player.GetGold() >= data.price) {
			player.GainGold(-data.price);
			player.AddItem(ItemFactory::CreateItem(id));

			std::string text = "[구매] " + data.name + "(을)를 구매하셨습니다.";
			UIManager::GetInstance().AddContent(UIType::Log, text);
		}
		else {
			UIManager::GetInstance().AddContent(UIType::Log, "[실패] 골드가 모자랍니다!");
		}
	}
	else {
		const auto& inventory = player.GetInventory();
		IItem* item = inventory[selected_index].get();
		const ItemData& data = ItemDataBase::GetData(item->GetID());

		player.GainGold(ItemDataBase::GetSellPrice(item->GetID()));
		player.RemoveItem(selected_index);

		std::string text = "[판매] " + data.name + "(을)를 판매하셨습니다.";
		UIManager::GetInstance().AddContent(UIType::Log, text);
	}
}
