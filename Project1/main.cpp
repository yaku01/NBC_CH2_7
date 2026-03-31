#include "Core/GameManager.h"
#include "Core/SaveLoadManager.h"
#include "Core/LogManager.h"
#include "Characters/Character.h"

int main()
{
	GameManager::GetInstance().Init();

	GameManager::GetInstance().Run();

	GameManager::GetInstance().Release();
    
    auto& player = Character::GetInstance();

    SaveLoadManager::Save(player);
	LogManager::GetInstance().SaveLogToFile("Log/Log.txt", player.GetName());
}
