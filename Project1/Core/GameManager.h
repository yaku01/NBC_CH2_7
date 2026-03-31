#pragma once
#include "Common/common.h"
#include <memory>
#include <queue>
#include <string>

class BaseScene;
class BattleManager;

class GameManager
{
public:
	static GameManager& GetInstance() {
		static GameManager instance;
		return instance;
	}

	GameManager(const GameManager&) = delete;
	GameManager& operator=(const GameManager&) = delete;

	void Init();
	void Run(); 
	void Release();
	void PushEvent(const Event& ev);

	BattleManager* GetBattleManager() const;

private:
	bool is_running = true;
	std::unique_ptr<BattleManager> battle_manager;

	// 씬 관련
	std::vector<std::unique_ptr<BaseScene>> scene_stack;
	SceneOp scene_op;
	SceneType next_scene;
	std::string next_scene_data;

	// 이벤트 큐
	std::queue<Event> event_queue;


	GameManager();
	~GameManager();

	void ProcessEvent();
	void ProcessInput();
	void ProcessScene();
};

