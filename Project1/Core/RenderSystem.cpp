#include "RenderSystem.h"

RenderSystem::RenderSystem()
{
    // width 에 0을 넣으면 글꼴에 어울리는 폭으로 자동 조절
    // Consolas 글꼴을 사용하므로 가로폭은 높이의 약 절반정도
    SetConsoleFont(0, 20);

    // 버퍼 2개 생성
    screen_buffers[0] = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0,
        NULL, CONSOLE_TEXTMODE_BUFFER, NULL);
    screen_buffers[1] = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0,
        NULL, CONSOLE_TEXTMODE_BUFFER, NULL);
    
    // 두 버퍼 모두 콘솔 사이즈 조절, 160, 60 으로 테스트
    // 1600*1200 정도의 해상도
    int width = 160;
    int height = 60;
    for (int i = 0; i < 2; ++i) { 
        SetConsoleSize(screen_buffers[i], width, height);
    }

    // 두 버퍼 모두 깜빡이는 커서 숨기기
    CONSOLE_CURSOR_INFO cci{};
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
    COORD coord = { 0, 0 }; // 시작 좌표
    DWORD text{};

    // 버퍼 정보 가져오기
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(screen_buffers[current_buffer_idx], &csbi);
    DWORD size = csbi.dwSize.X * csbi.dwSize.Y;    // 전체 콘솔 사이즈

    // Back Buffer 전체를 ' ' 로 채우기
    FillConsoleOutputCharacter(screen_buffers[current_buffer_idx], (TCHAR)' ',
        size, coord, &text);

    // 텍스트, 배경 색상 기본값으로 돌리기
    FillConsoleOutputAttribute(screen_buffers[current_buffer_idx], csbi.wAttributes,
        size, coord, &text);
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
    DWORD text{};
    COORD pos = { (short)x, (short)y };

    // 현재 그리고 있는 Back Buffer의 특정 좌표로 이동
    SetConsoleCursorPosition(screen_buffers[current_buffer_idx], pos);

    // Back Buffer에 문자열 출력
    WriteConsoleA(screen_buffers[current_buffer_idx],
        sv.data(), static_cast<DWORD>(sv.length()), &text, NULL);
}

int RenderSystem::GetScreenWidth() const
{
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(screen_buffers[current_buffer_idx], &csbi);
    return (csbi.srWindow.Right - csbi.srWindow.Left + 1);
}

int RenderSystem::GetScreenHeight() const
{
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(screen_buffers[current_buffer_idx], &csbi);
    return (csbi.srWindow.Bottom - csbi.srWindow.Top + 1);
}


//private 함수
void RenderSystem::SetConsoleSize(HANDLE handle, int width, int height)
{
    // 모니터에 띄울 수 있는 최대 칸 수
    COORD max_size = GetLargestConsoleWindowSize(handle);

    // 콘솔 사이즈 조절 시 최대 크기를 넘지 않게함
    int w = std::min(width, static_cast<int>(max_size.X));
    int h = std::min(height, static_cast<int>(max_size.Y));

    // 창크기 최소화
    // 기존보다 작게 할 때 오류 방지용
    SMALL_RECT rect = { 0, 0, 1, 1 };
    SetConsoleWindowInfo(handle, TRUE, &rect);

    // 버퍼 크기 설정
    COORD size = { static_cast<short>(w), static_cast<short>(h) };
    SetConsoleScreenBufferSize(handle, size);

    // 창 크기 버퍼 -1 로 맞추기
    rect.Right = w - 1;
    rect.Bottom = h - 1;
    SetConsoleWindowInfo(handle, TRUE, &rect);
}

void RenderSystem::SetConsoleFont(int width, int height)
{
    HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);

    CONSOLE_FONT_INFOEX cfi{};
    cfi.cbSize = sizeof(cfi);            // 구조체 크기
    cfi.nFont = 0;                       // 글꼴 인덱스
    cfi.dwFontSize.X = width;            // 너비
    cfi.dwFontSize.Y = height;           // 높이
    cfi.FontFamily = FF_DONTCARE;        // 폰트패밀리 적절하게 선택
    cfi.FontWeight = FW_BOLD;            // 굵게
    //cfi.FontWeight = FW_NORMAL;          // 보통
    wcscpy_s(cfi.FaceName, L"Consolas"); // 폭이 일정한 폰트 consolas

    SetCurrentConsoleFontEx(out, FALSE, &cfi);
}
