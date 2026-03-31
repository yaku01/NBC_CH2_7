#pragma once
#include "Common/common.h"
#include "BaseUI.h"
#include <vector>
#include <memory>
#include <fstream>

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
    void ToggleItemUI();
    int GetItemUICurrentPage() const;
    int GetItemUIItemsPerPage() const;
    void SaveLogToFile(const std::string& filename); //로그 파일 저장
    void LoadLogFromFile(const std::string& filename); //로그 파일 로드
    void ResetStats(); //로그 초기화

    // 디버그용 출력 확인용 메세지, 릴리즈 모드에선 사라짐
    static void TestMessage(std::string_view msg) {
#ifdef _DEBUG
        UIManager::GetInstance().AddContent(UIType::Log, msg);
#endif
    }
     

private:
    std::vector<std::unique_ptr<BaseUI>> uis;

    int count_attack_ = 0; //각 이벤트 횟수 저장 변수
    int count_damage_ = 0;
    int count_encounter_ = 0;
    int count_move_ = 0;
    int count_rest_ = 0;
    int count_reward_ = 0;
    int count_escape_ = 0;
    int count_death_ = 0;
    int count_use_ = 0;

    // 외부에서 new 못하도록 차단
    UIManager();
    ~UIManager();
};

