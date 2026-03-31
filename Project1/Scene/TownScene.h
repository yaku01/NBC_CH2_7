#pragma once
#include "ItemUsableScene.h"


class TownScene : public ItemUsableScene
{
public:
	TownScene() = default;

	void Init() override;
	void SetMenu() override;
	void ProcessNormalEvent(const Event& e) override;
	void Update(float delta_time) override;

private:
	int cost;
	
	void EnterInn();
};

