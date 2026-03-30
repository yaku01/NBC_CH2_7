#pragma once
#include "Common/common.h"
#include <vector>
#include <memory>
#include <string>

class Character;
class BaseUI;

class BaseScene
{
public:
	BaseScene();
	virtual ~BaseScene();

	virtual void Init() = 0;
	virtual void SetMenu() {}	// 선택지 메뉴 세팅
	virtual void ProcessEvent(const Event& e) = 0;
	virtual void Update(float delta_time) = 0;
	virtual void Render();		//	배경, 캐릭터 등의 render
	virtual void Release();
	virtual void SetSceneData(const std::string& data) {}

	void ChangeScene(SceneType scene);
	void PushScene(SceneType scene);
	void PushScene(SceneType scene, const std::string& path);
	void PopScene();
	bool IsOpaque() const;

protected:
	std::vector<std::unique_ptr<BaseUI>> scene_uis;
	bool is_opaque = true;
};

