#include "TownScene.h"
#include "Core/GameManager.h"
#include "Common/common.h"
#include "Characters/Character.h"
#include "UI/UIManager.h"
#include "Core/LogManager.h"
#include "UI/GameUI.h"

void TownScene::Init()
{
    ItemUsableScene::Init();

    // 일단 1휴식 = 100골드
    cost = 100;
    SetMenu();
}

void TownScene::SetMenu()
{
    auto bg = std::make_unique<AsciiUI>(0, 0);
    bg->LoadAsciiArt("Resource/village.txt");
    scene_uis.push_back(std::move(bg));

    UIManager::GetInstance().ClearContent(UIType::Menu); // 메뉴 비우기

    std::string menu_text = "1. 여관에서 휴식(" + std::to_string(cost) + "G)   2. 상점 진입   3. 던전 진입";
    UIManager::GetInstance().AddContent(UIType::Menu, menu_text);
    UIManager::GetInstance().AddContent(UIType::Menu, "원하는 행동을 선택하세요: ");
}

void TownScene::ProcessNormalEvent(const Event& e)
{
    if (e.type != EventType::KeyDown) {
        return;
    }

    SetMenu();

    switch (e.key_code) {
    case '1':
        EnterInn(); // 여관에서 휴식 시도
        break;

    case '2':
    {
        LogManager::GetInstance().AddLog("[이동] 상점에 들어갑니다");
        PushScene(SceneType::Shop, "Resource/Shop/Novice Village.txt");
        break;
    }

    case '3':
        LogManager::GetInstance().AddLog("[이동] 어두운 던전으로 향합니다...");
        ChangeScene(SceneType::Dungeon);
        break;

    case '.':
        Character::GetInstance().GainExp(100);
        break;
         
    default:
        UIManager::GetInstance().AddContent(UIType::Menu, "잘못된 입력입니다.");
        break;
    }
    
}

void TownScene::Update(float delta_time)
{
}


// private 함수
void TownScene::EnterInn()
{
    auto& player = Character::GetInstance();
    if (player.GetGold() >= cost) {
        LogManager::GetInstance().AddLog("[휴식] 여관에서 푹 쉬었습니다. (HP 회복)");
        
        std::string inn_text = "[소비] 여관에 " + std::to_string(cost) + "G 를 지불하였습니다.";
        LogManager::GetInstance().AddLog(inn_text);
        player.GainGold(-cost);
        player.RestoreHealth(player.GetMaxHealth());
    }
    else {
        LogManager::GetInstance().AddLog("[실패] 골드가 모자랍니다!");
    }
}
