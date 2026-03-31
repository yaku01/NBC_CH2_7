#include "SceneFactory.h"
#include "TitleScene.h"
#include "TownScene.h"
#include "DungeonScene.h"
#include "BattleScene.h"
#include "ExitPopUpScene.h"
#include "ShopScene.h"
#include "EncounterScene.h"
#include "EndingScene.h"
#include <functional>
#include <unordered_map>

using Func = std::function<std::unique_ptr<BaseScene>()>;

std::unique_ptr<BaseScene> SceneFactory::CreateScene(SceneType type)
{
	static const std::unordered_map<SceneType, Func> scene_creator = {
		{ SceneType::Title,	    []() { return std::make_unique<TitleScene>(); }},
		{ SceneType::Town,	    []() { return std::make_unique<TownScene>(); }},
		{ SceneType::Dungeon,	[]() { return std::make_unique<DungeonScene>(); }},
		{ SceneType::Battle,	[]() { return std::make_unique<BattleScene>(); }},
		{ SceneType::Exit,		[]() { return std::make_unique<ExitPopUpScene>(); }},
		{ SceneType::Shop,		[]() { return std::make_unique<ShopScene>(); }},
		{ SceneType::Encounter,	[]() { return std::make_unique<EncounterScene>(); }},
		{ SceneType::Ending,	[]() { return std::make_unique<EndingScene>(); }}
	};

	auto it = scene_creator.find(type);
	if (it != scene_creator.end()) {
		return it->second();
	}
	return nullptr;
} 
