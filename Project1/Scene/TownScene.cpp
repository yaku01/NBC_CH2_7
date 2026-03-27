#include "TownScene.h"
#include "Core/GameManager.h"
#include "Common/common.h"
#include "Characters/Character.h"
#include "UI/UIManager.h"


void TownScene::Init()
{
    SetMenu();
}

void TownScene::SetMenu()
{
    UIManager::GetInstance().ClearMessage(UIType::Menu); // 메뉴 비우기
    UIManager::GetInstance().AddMessage(UIType::Menu, "1. 여관에서 휴식  2. 던전으로 ");
    UIManager::GetInstance().AddMessage(UIType::Menu, "원하는 행동을 선택하세요: ");
}

void TownScene::ProcessEvent(const Event& e)
{
    if (e.type == EventType::KeyDown) {
        SetMenu();

        switch (e.key_code) {
        case '1':
            UIManager::GetInstance().AddMessage(UIType::Log, "[휴식] 여관에서 푹 쉬었습니다. (HP 회복)");
            // 회복 처리
            break;

        case '2':
            UIManager::GetInstance().AddMessage(UIType::Log, "[이동] 어두운 던전으로 향합니다...");
            ChangeScene(SceneType::Dungeon);
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

void TownScene::Update(float delta_time)
{
}

void TownScene::Release()
{

}
