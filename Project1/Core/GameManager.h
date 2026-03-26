#pragma once
#include "Common/common.h"
#include <memory>
#include <queue>

class BaseScene;
class BattleManager;
class Character;

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


	Character* GetPlayer() const;
	BattleManager* GetBattleManager() const;

private:
	bool is_running = true;
	Character* player = nullptr;
	std::unique_ptr<BattleManager> battle_manager;

	// 씬 관련
	std::vector<std::unique_ptr<BaseScene>> scene_stack;
	SceneOp scene_op;
	SceneType next_scene;

	// 이벤트 큐
	std::queue<Event> event_queue;


	GameManager();
	~GameManager();

	void ProcessInput();
	void ProcessScene();
	std::unique_ptr<BaseScene> CreateScene(SceneType type);

	//void GenerateMonsters();
};

