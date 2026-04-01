#ASCII Dungeon RPG 

📌 프로젝트 소개
------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
ASCII 아트를 활용한 콘솔 기반 RPG 게임입니다.
플레이어는 던전을 탐험하며 몬스터와 전투하고, 아이템을 획득하며 성장합니다.

이 프로젝트는 객체지향 설계(OOP) 를 기반으로
캐릭터, 아이템, 몬스터, UI, 씬(Scene)을 모듈화하여 구현되었습니다.

##🧩 주요 기능
------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
ASCII 아트를 활용한 콘솔 기반 RPG 게임입니다.
🧑‍💻 캐릭터 시스템
레벨, 체력, 공격력, 경험치 관리
장비(무기/방어구) 착용 및 해제
인벤토리 기반 아이템 관리

🎒 아이템 시스템
소비 아이템 (포션, 버프)
장비 아이템 (무기, 방어구)
팩토리 패턴을 이용한 아이템 생성

👾 몬스터 시스템
다양한 몬스터 (Slime, Goblin, Orc, Troll, Boss)
랜덤 생성 및 드롭 시스템
속도 기반 턴 시스템

⚔️ 전투 시스템
턴 기반 전투
게이지 기반 행동 순서
보상 (골드, 경험치, 아이템)

🗺️ 씬(Scene) 시스템
Title / Town / Dungeon / Battle / Shop / Ending
Scene Stack 기반 상태 관리
이벤트 큐 기반 입력 처리

🖥️ UI 시스템
ASCII 기반 UI 출력
로그창, 인벤토리, 상태창
UI Manager를 통한 통합 관리

🏗️ 구조 설계
핵심 구조
Character : 플레이어 데이터 및 행동 관리
Item (IItem) : 인터페이스 기반 아이템 구조
Monster : 상속 기반 몬스터 구조
Scene : 게임 상태 관리
UI : 화면 출력 담당
Manager : 전체 흐름 제어



🧠 설계 패턴
Singleton Pattern
→ GameManager, UIManager, ResourceManager
Factory Pattern
→ ItemFactory, MonsterFactory, SceneFactory
Inheritance (상속 구조)
→ Monster, Item, Scene, UI
Composition
→ Character → Inventory / Equipment

🖼️ 실행 화면 (예시)
던전 탐험
전투 화면
인벤토리 UI
ASCII 아트 기반 캐릭터 및 몬스터


⚙️ 개발 환경
Language : C++
IDE : Visual Studio
Platform : Windows Console
Standard : C++17 이상

🚀 실행 방법
프로젝트 클론
git clone <repository-url>
Visual Studio에서 프로젝트 열기
빌드 후 실행

Ctrl + F5
💾 저장 / 로드 기능
플레이어 상태 저장
이름 기반 로드 시스템

###📂 주요 클래스 구조
Character
IItem / ConsumableItem / EquippableItem
Monster / Slime / Goblin / Orc / Troll / BossMonster
GameManager / BattleManager
BaseScene / BattleScene / TownScene / DungeonScene
BaseUI / InventoryUI / LogUI / AsciiUI
