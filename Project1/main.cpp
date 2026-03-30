#include "Core/GameManager.h"
#include <windows.h>

void SetConsoleFont(int fontSizeX, int fontSizeY) {
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_FONT_INFOEX cfi;

    cfi.cbSize = sizeof(cfi);
    cfi.nFont = 0;

    // 폰트 가로, 세로 크기 설정, 픽셀 단위
    cfi.dwFontSize.X = fontSizeX; // 0으로 설정하면 비율에 맞춰 자동 조절
    cfi.dwFontSize.Y = fontSizeY; // 글자 높이

    cfi.FontFamily = FF_DONTCARE;
    //cfi.FontWeight = FW_NORMAL; // 일반
    cfi.FontWeight = FW_BOLD;   // 두껍게

    // 사용할 폰트 이름
    wcscpy_s(cfi.FaceName, L"Consolas");

    SetCurrentConsoleFontEx(hOut, FALSE, &cfi);
}

int main()
{
    SetConsoleFont(0, 20);

	GameManager::GetInstance().Init();

	GameManager::GetInstance().Run();

	GameManager::GetInstance().Release();

}