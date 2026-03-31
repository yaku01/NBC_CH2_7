#include "DungeonScene.h"
#include "UI/UIManager.h"
#include "UI/GameUI.h"
#include "Core/RenderSystem.h"
#include "Characters/Character.h"
#include "Core/LogManager.h"


void DungeonScene::Init()
{
    ItemUsableScene::Init();

    // -----------
    //배경
    auto bg = std::make_unique<AsciiUI>(0, 0);
    bg->LoadAsciiArt("bg.txt");
    scene_uis.push_back(std::move(bg));


    SetMenu();
}
 
void DungeonScene::SetMenu()
{
    UIManager::GetInstance().ClearContent(UIType::Menu);
    if (Character::GetInstance().IsMaxLevel()) {
        UIManager::GetInstance().AddContent(UIType::Menu, "이 앞에서 강력한 기운이 느껴집니다... ");
    }
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
        LogManager::GetInstance().AddLog( "[조우] 몬스터와 조우했습니다!");

        // data가 1이면 보스전 진입
        if (Character::GetInstance().IsMaxLevel()) {
            PushScene(SceneType::Encounter, SceneType::Battle, 2.f, 1);
        }
        else {
            PushScene(SceneType::Encounter, SceneType::Battle, 2.f, 0);
        }
        break;

    case '2':
        LogManager::GetInstance().AddLog( "[이동] 마을로 귀환합니다...");
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
