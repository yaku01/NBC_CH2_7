#include "TitleScene.h"
#include "Core/GameManager.h"
#include "Common/common.h"
#include "Characters/Character.h"
#include "UI/UIManager.h"
#include "UI/GameUI.h"
#include "Core/DungeonMapState.h"
#include "Core/SaveLoadManager.h"

constexpr int MAX_NAME_LENGTH = 10;

void TitleScene::Init()
{
    // -----------
    //배경
    auto bg = std::make_unique<AsciiUI>(0, 0);
    bg->LoadAsciiArt("Resource/title.txt");
    scene_uis.push_back(std::move(bg));

    UIManager::GetInstance().SetAllVisible(false);
    UIManager::GetInstance().SetVisible(UIType::Menu, true);

    SetMenu();
}

void TitleScene::SetMenu()
{
    UIManager::GetInstance().ClearContent(UIType::Menu);
    UIManager::GetInstance().AddContent(UIType::Menu, "이름을 입력하세요 : " + name);
}

void TitleScene::ProcessEvent(const Event& e)
{
    if (e.type != EventType::KeyDown) {
        return;
    }

    SetMenu();
    
    // 알파벳 입력시 이름 입력
   if ((e.key_code >= 'a' && e.key_code <= 'z') || (e.key_code >= 'A' && e.key_code <= 'Z') || 
       (e.key_code >= '0' && e.key_code <= '9'))
   {
        if (name.size() < MAX_NAME_LENGTH) {
            name += char(e.key_code);
        }
        SetMenu();
    }
    // 엔터 입력 시 로그인 시도
    else if (e.key_code == '\r') {
       if (!name.empty()) {
           Character::GetInstance(name);
           DungeonMapState::ResetToFirstMap();

           auto& player = Character::GetInstance(name);

           player.Reset();
           player.SetName(name);

           SaveLoadManager::Load(player, name);
           
           ChangeScene(SceneType::Town);
       }
    }
    // 백스페이스 입력 시 이름 지우기
    else if (e.key_code == '\b') {
        if (!name.empty()) {
            name.pop_back();
        }
        SetMenu();
    }
    else {
        UIManager::GetInstance().AddContent(UIType::Menu, "잘못 입력하셨습니다. 다시 입력해주세요.");
    }
}

void TitleScene::Update(float delta_time)
{
}

bool TitleScene::IsExitable() const
{
    return false;
} 
