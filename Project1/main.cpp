#include "GameManager.h"

int main()
{
	GameManager::GetInstance().Init();

	GameManager::GetInstance().Run();

	GameManager::GetInstance().Release();
}