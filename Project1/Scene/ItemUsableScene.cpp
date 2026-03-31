#include "ItemUsableScene.h"
#include "UI/GameUI.h"
#include "UI/UIManager.h"
#include "Characters/Character.h"
#include "Core/RenderSystem.h"
#include "Core/LogManager.h"


ItemUsableScene::ItemUsableScene() = default;
ItemUsableScene::~ItemUsableScene() = default;

void ItemUsableScene::Init()
{
	int w = RenderSystem::GetInstance().GetScreenWidth();
	int h = RenderSystem::GetInstance().GetScreenHeight();

	int x = static_cast<int>(w * 0.2f);
	int y = static_cast<int>(h * 0.2f);
	int width = static_cast<int>(w * 0.4f);
	int height = 8;

	item_popup_ui = std::make_unique<ItemConfirmUI>(x, y, width, height);
}

void ItemUsableScene::ProcessEvent(const Event& e)
{
	if (e.type != EventType::KeyDown) {
		return;
	}

	switch (input_state) {

		// 일반 조작
	case InputState::Normal:
		ProcessNormalMode(e);
		break;

	case InputState::InventoryMode:
		ProcessInventoryMode(e);
		break;

	case InputState::ItemConfirm:
		ProcessItemConfirm(e);
		break;
	}
}

void ItemUsableScene::Update(float delta_time)
{
}

void ItemUsableScene::Render()
{
	BaseScene::Render();

	if (item_popup_ui) {
		item_popup_ui->Render();
	}
}

void ItemUsableScene::ProcessNormalMode(const  Event& e)
{
	switch (e.key_code) {
	case 'i':
	case 'I':
		input_state = InputState::InventoryMode;
		UIManager::GetInstance().ToggleItemUI();
		break;

	case 'q':
	case 'Q':
		UIManager::GetInstance().PrevPageItemUI();
		break;

	case 'e':
	case 'E':
		UIManager::GetInstance().NextPageItemUI();
		break;

	default:
		ProcessNormalEvent(e);
	}
}

void ItemUsableScene::ProcessInventoryMode(const  Event& e)
{
	switch (e.key_code) {
	case 'i':
	case 'I':
		input_state = InputState::Normal;
		UIManager::GetInstance().ToggleItemUI();
		break;

	case 'q':
	case 'Q':
		UIManager::GetInstance().PrevPageItemUI();
		break;

	case 'e':
	case 'E':
		UIManager::GetInstance().NextPageItemUI();
		break;

	default:
	{
		int idx = e.key_code - '0';
		if (idx < 1 || idx > 9) {
			return;
		}

		const auto& inventory = Character::GetInstance().GetInventory();

		// 현재 ItemUI의 페이지, 페이지당 개수 가져오기
		int current_page = UIManager::GetInstance().GetItemUICurrentPage();
		int ITEMS_PER_PAGE = UIManager::GetInstance().GetItemUIItemsPerPage();
		size_t target_idx = static_cast<size_t>(current_page * ITEMS_PER_PAGE + (idx - 1));

		if (target_idx < inventory.size()) {
			item_index = target_idx;
			input_state = InputState::ItemConfirm;

			// 팝업 띄울 아이템 타게팅
			item_popup_ui->SetTarget(inventory[target_idx]->GetID());
			item_popup_ui->SetActionText("사용하시겠습니까?");
		}
		
		break;
	}

	}
}

void ItemUsableScene::ProcessItemConfirm(const  Event& e)
{
	switch (e.key_code) {
	case 'y':
	case 'Y':
	case '\r':
		Character::GetInstance().UseItem(item_index);
		LogManager::GetInstance().AddLog( "[사용] 아이템을 사용했습니다.");

		item_popup_ui->SetTarget(ItemID::None); // 팝업 닫기
		input_state = InputState::InventoryMode;
		break;

	case 'n':
	case 'N':
		item_popup_ui->SetTarget(ItemID::None);
		input_state = InputState::InventoryMode;
		break;
	}
}
