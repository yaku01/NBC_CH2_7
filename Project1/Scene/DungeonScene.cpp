#include "DungeonScene.h"
#include "UI/UIManager.h"
#include "UI/GameUI.h"
#include "Core/RenderSystem.h"
#include "Core/DungeonMapState.h"

void DungeonScene::Init()
{
    ItemUsableScene::Init();

    // -----------
    //배경
    auto bg = std::make_unique<AsciiUI>(0, 0);
    bg->LoadAsciiArt(DungeonMapState::GetCurrentMapPath());
    scene_uis.push_back(std::move(bg));


    SetMenu();
}

void DungeonScene::SetMenu()
{
    UIManager::GetInstance().ClearContent(UIType::Menu);
    UIManager::GetInstance().AddContent(UIType::Menu, "1. 내부 탐색 (몬스터 조우)   2. 마을로 귀환한다 ");
    UIManager::GetInstance().AddContent(UIType::Menu, "어떤 행동을 하시겠습니까?: ");
}

void DungeonScene::ProcessNormalEvent(const Event& e)
{
    if (e.type != EventType::KeyDown) {
        return;
    }

    SetMenu();

    switch (e.key_code) {
    case '1':
    {
        UIManager::GetInstance().AddContent(UIType::Log, "[조우] 몬스터와 조우했습니다!");
        int next_scene = static_cast<int>(SceneType::Battle);
        float max_time = 3.f;

        PushScene(SceneType::Encounter, std::to_string(next_scene) + " " + std::to_string(max_time));
        break;
    }

    case '2':
        UIManager::GetInstance().AddContent(UIType::Log, "[이동] 마을로 귀환합니다...");
        ChangeScene(SceneType::Town);
        break;
    
    default:
        UIManager::GetInstance().AddContent(UIType::Menu, "잘못된 입력입니다.");
        break;
    }
}

void DungeonScene::Update(float delta_time)
{
}
