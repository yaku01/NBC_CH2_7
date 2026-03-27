#include "DungeonScene.h"
#include "UI/UIManager.h"
#include "UI/GameUI.h"
#include "Core/RenderSystem.h"


void DungeonScene::Init()
{
    // -----------
    //배경
    auto bg = std::make_unique<AsciiUI>(0, 0);
    bg->LoadAsciiArt("bg.txt");
    scene_uis.push_back(std::move(bg));


    SetMenu();
}

void DungeonScene::SetMenu()
{
    UIManager::GetInstance().ClearMessage(UIType::Menu);
    UIManager::GetInstance().AddMessage(UIType::Menu, "1. 내부 탐색 (몬스터 조우)   2. 마을로 귀환한다 ");
    UIManager::GetInstance().AddMessage(UIType::Menu, "어떤 행동을 하시겠습니까?: ");
}

void DungeonScene::ProcessEvent(const Event& e)
{
    if (e.type == EventType::KeyDown) {
        SetMenu();

        switch (e.key_code) {
        case '1':
            UIManager::GetInstance().AddMessage(UIType::Log, "[조우] 몬스터와 조우했습니다!");
            PushScene(SceneType::Battle);
            break;

        case '2':
            UIManager::GetInstance().AddMessage(UIType::Log, "[이동] 마을로 귀환합니다...");
            ChangeScene(SceneType::Town);
            break;

        case 'q':
        case 'Q':
            UIManager::GetInstance().PrevPageItemUI();
            break;

        case 'e':
        case 'E':
            UIManager::GetInstance().NextPageItemUI();
            break;

        default:
            UIManager::GetInstance().AddMessage(UIType::Menu, "잘못된 입력입니다.");
            break;
        }
    }
}

void DungeonScene::Update(float delta_time)
{
}

void DungeonScene::Release()
{
}
