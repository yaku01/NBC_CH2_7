#include <thread>
#include <conio.h>
#include "GameManager.h"
#include "Character.h"
#include "BattleManager.h"

#include <iostream>

GameManager::GameManager()
{
	is_running = true;
}

GameManager::~GameManager()
{
}

void GameManager::Init()
{
	player = std::make_unique<Character>();
	
	battle_manager = std::make_unique<BattleManager>(player.get());
	battle_manager->Init();

	// 임시
	GenerateMonsters();
}

// 게임 루프 
void GameManager::Run()
{
	// 60fps -> 1프레임당 약16.66ms
	constexpr float delta_time = 1.f / 60.f;

	auto last = std::chrono::steady_clock::now();
	float accumulator = 0.f;	// 경과한 시간 누적

	while (is_running) {
		auto current = std::chrono::steady_clock::now();
		std::chrono::duration<float> elapsed = current - last;
		last = current;

		// 이번 루프에 걸린 시간
		accumulator += elapsed.count();

		// KeyDown 이벤트 감지
		ProcessInput();

		// 이벤트 처리
		while (!event_queue.empty()) {
			Event ev = event_queue.front();
			event_queue.pop();

			switch (ev.type) {
			case EventType::KeyDown:
				ProcessEvent(ev);
				break;

			case EventType::Quit:
				is_running = false;
				break;
			}
		}

		// 16.66ms가 지났다면 update, render
		if (accumulator >= delta_time) {
			// 만약 렉으로 처리가 늦어 시간이 밀렸다면 반복해서 처리
			while (accumulator >= delta_time) {
				Update(delta_time);
				accumulator -= delta_time;
			}

			Render();
		}

		// 짧게 휴식
		std::this_thread::sleep_for(std::chrono::milliseconds(1));
	}
}

void GameManager::Release()
{

}

// private 함수
void GameManager::GenerateMonsters()
{
	// 레벨 부여
	int level = 1;

	// 전투 관리에서 몬스터 생성
	// 몬스터는 전투할때만 필요함
	battle_manager->GenerateMonster(level);
}

void GameManager::Battle()
{
	
}

void GameManager::DisplayInventory()
{
}

void GameManager::ProcessInput()
{
	if (_kbhit()) {
		int key = _getch();

		Event ev{};
		ev.type = EventType::KeyDown;
		ev.key_code = key;
		event_queue.push(ev);
	}
}

void GameManager::ProcessEvent(const Event& e)
{
	if (e.type != EventType::KeyDown) {
		return;
	}

	// 키보드 입력 처리	
	switch (scene) {
		case Scene::Title:
			// 타이틀
			break;

		case Scene::Town:
			// 타이틀
			break;

		case Scene::Dungeon:
			// 타이틀
			break;

		case Scene::Battle:
			ProcessBattleScene(e.key_code);
			break;

		default:
			// 오류
			break;
	}
}

void GameManager::Update(float delta_time)
{

}

void GameManager::Render()
{

}

void GameManager::ProcessBattleScene(int key_code)
{
	int idx = key_code - '1';
	
	if (idx >= 0 && idx < battle_manager->GetMonsterSize()) {
		// 플레이어 공격
		battle_manager->PlayerAttack(idx);

		// 몬스터 공격
		if (!battle_manager->IsBattleOver()) {
			battle_manager->MonstersAttack();
		}

		// 전투 종료 판단
		if (battle_manager->IsBattleOver()) {
			// 플레이어 사망으로 종료라면
			if (player->GetHp() <= 0) {
				// 게임 오버
				// --
			}
			else {	// 플레이어 승리라면
				battle_manager->DistributedReward();
				std::cout << "전투 승리!" << std::endl;
				return;
			}
		}
	}

}
