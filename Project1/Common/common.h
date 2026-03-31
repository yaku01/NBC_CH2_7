#pragma once
#define NOMINMAX
#include <string>
#include <vector>

namespace RandomUtil {
	int GetRange(int min, int max);
	double GetRange(double min, double max);
	bool IsSuccess(double probability);
	void Shuffle(std::vector<int>& v); 
}

enum class UIType {
	Menu,
	CharacterInfo,
	Log,
	Inventory,
	KillLog,
	COUNT
};

enum class EventType {
	KeyDown,
	KeyUp,
	ChangeScene,	// 새로운 씬으로 전환
	PushScene,		// 현재 씬을 멈추고 새로운 씬 띄움
	PopScene,		// 현재 씬 끄고 아래에 있던 씬으로 복귀
	ReplaceScene,
	Quit
};

enum class SceneOp { 
	Change,
	Push, 
	Pop, 
	Replace,
	None 
};

enum class SceneType {
	Title,
	Town,
	Dungeon,
	Battle,
	Exit,
	Shop,
	Encounter,
	Ending,
	None
};

struct Event {
	EventType type;

	// 같은 메모리 공간을 겹쳐서 사용
	union {
		int key_code;
		SceneType next_scene;
	};
	std::string scene_data;
};

enum class MonsterType {
	Slime, 
	Troll,
	Goblin,
	Orc,
	Boss,
	None
};
