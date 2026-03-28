#pragma once
#define NOMINMAX

namespace RandomUtil {
	int GetRange(int min, int max);
	bool IsSuccess(double probability);
}

enum class UIType {
	Menu,
	CharacterInfo,
	Log,
	Item,
	KillLog,
	COUNT
};

enum class EventType {
	KeyDown,
	KeyUp,
	ChangeScene,	// 새로운 씬으로 전환
	PushScene,		// 현재 씬을 멈추고 새로운 씬 띄움
	PopScene,		// 현재 씬 끄고 아래에 있던 씬으로 복귀
	Quit
};

enum class SceneOp { Change, Push, Pop, None };

enum class SceneType {
	Title,
	Town,
	Dungeon,
	Battle,
	Exit,
	None
};

struct Event {
	EventType type;

	// 같은 메모리 공간을 겹쳐서 사용
	union {
		int key_code;
		SceneType next_scene;
	};
};


enum class MonsterType {
	Slime, 
	Troll,
	Goblin,
	Orc,
	None
};