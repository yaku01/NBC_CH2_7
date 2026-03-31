#pragma once
#include "ItemUsableScene.h"

class DungeonScene : public ItemUsableScene
{
public:
	DungeonScene() = default;

	void Init() override;
	void SetMenu() override;
	void ProcessNormalEvent(const Event& e) override;
	void Update(float delta_time) override; 
};

