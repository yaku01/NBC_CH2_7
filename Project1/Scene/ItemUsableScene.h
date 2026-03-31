#pragma once
#include "BaseScene.h"

enum class InputState { Normal, InventoryMode, ItemConfirm };

class ItemConfirmUI;

class ItemUsableScene : public BaseScene
{
public:
	ItemUsableScene();
	virtual ~ItemUsableScene();

	virtual void Init() override;
	virtual void ProcessEvent(const Event& e) override final;
	virtual void Update(float delta_time) override;
	virtual void Render() override;

protected:
	std::unique_ptr<ItemConfirmUI> item_popup_ui;
	InputState input_state = InputState::Normal;
	size_t item_index = 0;

	// 아이템 사용 아닐 때 이벤트 처리
	// 자식클래스에서 처리하는 함수
	virtual void ProcessNormalEvent(const Event& e) = 0;

private:
	void ProcessNormalMode(const  Event& e);
	void ProcessInventoryMode(const  Event& e);
	void ProcessItemConfirm(const  Event& e);
};

