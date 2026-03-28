#include "RenderSystem.h"

RenderSystem::RenderSystem()
{
    // 버퍼 2개 생성
    screen_buffers[0] = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0,
        NULL, CONSOLE_TEXTMODE_BUFFER, NULL);
    screen_buffers[1] = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0,
        NULL, CONSOLE_TEXTMODE_BUFFER, NULL);
    
    // 두 버퍼 모두 깜빡이는 커서 숨기기
    CONSOLE_CURSOR_INFO cci;
    cci.dwSize = 1;
    cci.bVisible = FALSE;
    SetConsoleCursorInfo(screen_buffers[0], &cci);
    SetConsoleCursorInfo(screen_buffers[1], &cci);
}

RenderSystem::~RenderSystem()
{
    CloseHandle(screen_buffers[0]);
    CloseHandle(screen_buffers[1]);
}

void RenderSystem::ClearBuffer()
{
    COORD coordScreen = { 0, 0 };
    DWORD cCharsWritten;
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(screen_buffers[current_buffer_idx], &csbi);
    DWORD dwConSize = csbi.dwSize.X * csbi.dwSize.Y;

    // Back Buffer 전체를 공백(' ')으로 채워서 싹 지워버림
    FillConsoleOutputCharacter(screen_buffers[current_buffer_idx], (TCHAR)' ',
        dwConSize, coordScreen, &cCharsWritten);
    FillConsoleOutputAttribute(screen_buffers[current_buffer_idx], csbi.wAttributes,
        dwConSize, coordScreen, &cCharsWritten);
}

void RenderSystem::Draw()
{
    // 화면에 완성된 Back Buffer 띄우기
    SetConsoleActiveScreenBuffer(screen_buffers[current_buffer_idx]);

    // 그릴 버퍼 교체
    current_buffer_idx = (current_buffer_idx + 1) % 2;
}

void RenderSystem::PrintText(int x, int y, std::string_view sv)
{
    DWORD dwCharsWritten;
    COORD pos = { (short)x, (short)y };

    // 현재 그리고 있는 Back Buffer의 특정 좌표로 이동
    SetConsoleCursorPosition(screen_buffers[current_buffer_idx], pos);

    // Back Buffer에 문자열 출력
    WriteConsoleA(screen_buffers[current_buffer_idx],
        sv.data(), static_cast<DWORD>(sv.length()), &dwCharsWritten, NULL);
}

int RenderSystem::GetScreenWidth()
{
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
    return (csbi.srWindow.Right - csbi.srWindow.Left + 1);
}

int RenderSystem::GetScreenHeight()
{
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
    return (csbi.srWindow.Bottom - csbi.srWindow.Top + 1);
}
