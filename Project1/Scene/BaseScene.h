#pragma once
#include "Common/common.h"

class Character;

class BaseScene
{
public:
	BaseScene();
	virtual ~BaseScene() = default;

	virtual void Init() = 0;
	virtual void SetUI() {}		// 씬 전용 로컬 UI 세팅
	virtual void SetMenu() {}	// 선택지 메뉴 세팅
	virtual void ProcessEvent(const Event& e) = 0;
	virtual void Update(float delta_time) = 0;
	virtual void Render() = 0;		//	배경, 캐릭터 등의 render
	virtual void Release() = 0;

	void ChangeScene(SceneType scene);
	void PushScene(SceneType scene);
	void PopScene();
	bool IsOpaque() const;

protected:
	bool is_opaque = true;
	Character* player = nullptr;
};

