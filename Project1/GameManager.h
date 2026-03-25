#pragma once
#include <memory>
#include <queue>

class BattleManager;
class Character;

enum class Scene {
	Title, Town, Dungeon, Battle, None
};

enum class EventType {
	KeyDown,
	Quit
};

struct Event {
	EventType type;
	int key_code;
};

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

private:
	bool is_running = true;
	std::unique_ptr<Character> player;
	std::unique_ptr<BattleManager> battle_manager;
	std::queue<Event> event_queue;
	Scene scene = Scene::Battle;

	GameManager();
	~GameManager();

	void GenerateMonsters();
	void Battle();
	void DisplayInventory();
	void ProcessInput();
	void ProcessEvent(const Event& ev);
	void Update(float delta_time);
	void Render();

	void ProcessBattleScene(int key_code);
};

