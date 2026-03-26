#include "TitleScene.h"
#include "Core/GameManager.h"
#include "Common/common.h"
#include "UI/UIManager.h"

void TitleScene::Init()
{
    SetUI();
    SetMenu();
}

void TitleScene::SetUI()
{
}

void TitleScene::SetMenu()
{
    UIManager::GetInstance().ClearMessage(UIType::Menu);
    UIManager::GetInstance().AddMessage(UIType::Menu, "1. 게임 시작   2. 게임 종료");
    UIManager::GetInstance().AddMessage(UIType::Menu, "원하는 메뉴의 번호를 입력하세요: ");
}

void TitleScene::ProcessEvent(const Event& e)
{
    if (e.type == EventType::KeyDown) {
        SetMenu();

        switch (e.key_code) {
        case '1':
            ChangeScene(SceneType::Town);
            break;

        case '2':
        {
            Event ev{};
            ev.type = EventType::Quit;
            GameManager::GetInstance().PushEvent(ev);
            break;
        }

        default:
            UIManager::GetInstance().AddMessage(UIType::Menu, "잘못 입력하셨습니다. 다시 입력해주세요.");
            break;
        }
    }
}

void TitleScene::Update(float delta_time)
{
}

void TitleScene::Render()
{
}

void TitleScene::Release()
{
}

