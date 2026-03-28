#pragma once
#include "Common/common.h"
#include "BaseUI.h"
#include <vector>
#include <memory>

class UIManager 
{
public:
    // 이 함수로 UIManager에 접근
    static UIManager& GetInstance() {
        static UIManager instance;
        return instance;
    }

    // 복사 생성자와 대입 연산자 삭제
    // 실수로 객체가 복사되는 것 차단
    UIManager(const UIManager&) = delete;
    UIManager& operator=(const UIManager&) = delete;

    void AddContent(UIType type, std::string_view msg);
    void ClearContent(UIType type);
    void ClearAll(const std::vector<UIType>& ignore_list = {});
    void Render();  // 로그, 선택지 그리기
    void SetVisible(UIType type, bool value);
    void SetAllVisible(bool value = true);
    void NextPageItemUI();
    void PrevPageItemUI();
    void OnMonsterKilled(const std::string& monster_name); // 킬보드에 킬 추가


    // 디버그용 출력 확인용 메세지, 릴리즈 모드에선 사라짐
    static void TestMessage(std::string_view msg) {
#ifdef _DEBUG
        UIManager::GetInstance().AddContent(UIType::Log, msg);
#endif
    }

private:
    std::vector<std::unique_ptr<BaseUI>> uis;

    // 외부에서 new 못하도록 차단
    UIManager();
    ~UIManager();
};

