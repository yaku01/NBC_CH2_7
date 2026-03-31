#pragma once
#include "Common/common.h"
#include "Core/GameManager.h"
#include <vector>
#include <memory>
#include <string>
#include <sstream>

class Character;
class BaseUI;
 

// decltype(auto) -> 값에 맞는 타입 추출
// &인지 복사본인지 추론
// 임시객체가 들어올 수 있으므로 인자는 && 여야 함
template <typename T>
decltype(auto) EnumToInt(T&& val) {
	// decay_t<T> 는 const나 & 를 제외한 순수 자료형을 받음
	using DecayT = std::decay_t<T>;

	// if constexpr 를 사용해야 컴파일 에러 X
	if constexpr (std::is_enum_v<DecayT>) {
		return static_cast<std::underlying_type_t<DecayT>>(val);
	}
	else {
		return std::forward<T>(val);
	}
}

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

	template<typename... Args>
	void ChangeScene(SceneType scene, Args... args);

	template<typename... Args>
	void PushScene(SceneType scene, Args... args);

	template<typename... Args>
	void ReplaceScene(SceneType scene, Args... args);

	void PopScene();

	bool IsOpaque() const;
	virtual bool IsExitable() const;

protected:
	std::vector<std::unique_ptr<BaseUI>> scene_uis;
	bool is_opaque = true;

private:
	template<typename... Args>
	void SendSceneEvent(EventType event_type, SceneType next_scene, Args&&... args);
};


template<typename ...Args>
inline void BaseScene::SendSceneEvent(EventType event_type, SceneType next_scene, Args && ...args)
{
	Event ev{};
	ev.type = event_type;
	ev.next_scene = next_scene;
	
	// 가변인자가 있다면
	if constexpr (sizeof...(args) > 0) {
		std::ostringstream oss;

		// enum은 int로 변환하고 아닌경우는 그냥 oss에 넣고 공백 추가
		((oss << EnumToInt(std::forward<Args>(args)) << " "), ...);

		// 마지막 공백 제거
		ev.scene_data = oss.str();
		ev.scene_data.pop_back();
	}

	GameManager::GetInstance().PushEvent(ev);
}

template<typename ...Args>
inline void BaseScene::ChangeScene(SceneType scene, Args ...args)
{
	SendSceneEvent(EventType::ChangeScene, scene, std::forward<Args>(args)...);
}

template<typename ...Args>
inline void BaseScene::PushScene(SceneType scene, Args ...args)
{
	SendSceneEvent(EventType::PushScene, scene, std::forward<Args>(args)...);
}

template<typename ...Args>
inline void BaseScene::ReplaceScene(SceneType scene, Args ...args)
{
	SendSceneEvent(EventType::ReplaceScene, scene, std::forward<Args>(args)...);
}

