#include <windows.h>
#include <tchar.h>
#include "Map.h"
#include "Image.h"
#include "Character.h"
#include "MonsterSpawner.h"
#include "Gumiho.h"
#include "ShadowGhost.h"

#pragma comment(lib, "gdiplus.lib")

Map VillageMap;

Character* player = nullptr;
MonsterSpawner* oniSpawner = nullptr;
MonsterSpawner* gumihoSpawner = nullptr;
MonsterSpawner* shadowSpawner = nullptr;

ULONG_PTR gdiplusToken;

RECT wallRect =
{
    300,200,450,350
};

LARGE_INTEGER frequency;
LARGE_INTEGER previousTime;
LARGE_INTEGER currentTime;

HINSTANCE g_hInst;
LPCTSTR lpszClass = L"OBU_Project";
LPCTSTR lpszWindowName = L"OBU_Project";
LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam);

int WINAPI WinMain(

    HINSTANCE hInstance,
    HINSTANCE hPrevInstance,
    LPSTR lpszCmdParam,
    int nCmdShow)
{
    Gdiplus::GdiplusStartupInput gdiplusInput;

    Gdiplus::Status status = Gdiplus::GdiplusStartup(
        &gdiplusToken,
        &gdiplusInput,
        nullptr
    );

    if (status != Gdiplus::Ok)
    {
        MessageBox(
            nullptr,
            L"GDI+ 초기화 실패",
            L"Error",
            MB_OK
        );

        return 0;
    }

    HWND hWnd;
    MSG Message = {};
    WNDCLASSEX WndClass = {};

    g_hInst = hInstance;

    WndClass.cbSize = sizeof(WNDCLASSEX);
    WndClass.style = CS_HREDRAW | CS_VREDRAW;
    WndClass.lpfnWndProc = WndProc;
    WndClass.cbClsExtra = 0;
    WndClass.cbWndExtra = 0;
    WndClass.hInstance = hInstance;
    WndClass.hIcon = LoadIcon(nullptr, IDI_APPLICATION);
    WndClass.hCursor = LoadCursor(nullptr, IDC_ARROW);
    WndClass.hbrBackground =
        static_cast<HBRUSH>(GetStockObject(BLACK_BRUSH));
    WndClass.lpszMenuName = nullptr;
    WndClass.lpszClassName = lpszClass;
    WndClass.hIconSm = LoadIcon(nullptr, IDI_APPLICATION);

    RegisterClassEx(&WndClass);

    hWnd = CreateWindow(lpszClass,lpszWindowName,WS_OVERLAPPEDWINDOW,0,0,775,600,nullptr,nullptr,hInstance,nullptr);

    ShowWindow(hWnd, nCmdShow);
    UpdateWindow(hWnd);

    while (GetMessage(&Message, nullptr, 0, 0))
    {
        TranslateMessage(&Message);
        DispatchMessage(&Message);
    }

    Gdiplus::GdiplusShutdown(gdiplusToken);

    return static_cast<int>(Message.wParam);
}



LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	PAINTSTRUCT ps;

	HDC hDC;

    switch (uMsg) {

    case WM_CREATE:
    {
        if (!VillageMap.LoadImages())
        {
           // MessageBox(hWnd, L"맵 이미지 로드 실패", L"Error", MB_OK);
        }

        player = new Character( L"Image\\character\\character_3_frame16x20.png");

        oniSpawner = new MonsterSpawner(MonsterType::Oni,
            15 * Tile_Size,   // 타일 X = 15 (큰 크리스탈 쪽으로 가까이 가면 뜸)
            8 * Tile_Size,    // 타일 Y = 6
            100.0f,    // 플레이어가 400 안으로 오면 생성
            250.0f,    // 몬스터 탐지 범위
            80.0f,     // 몬스터 공격 범위
            L"Image\\monster_oni\\Walk.png",
            L"Image\\monster_oni\\Attack.png"
        );

        gumihoSpawner = new MonsterSpawner(MonsterType::Gumiho,15*Tile_Size,8*Tile_Size,100.0f,250.0f,80.0f, 
            L"Image\\monster_gumiho\\Run.png",
            L"Image\\monster_gumiho\\Attack.png");

        shadowSpawner = new MonsterSpawner(MonsterType::ShadowGhost,15*Tile_Size,8*Tile_Size,100.0f,0.0f,0.0f,
            L"Image\\monster_shadow\\warning.png",
            L"Image\\monster_shadow\\attack.png");//그림자 귀신도 임시

        QueryPerformanceFrequency(&frequency);
        QueryPerformanceCounter(&previousTime);

        SetTimer(hWnd, 1, 7, nullptr);

        return 0;
    }


    case WM_PAINT:
    {
        hDC = BeginPaint(hWnd, &ps);

        RECT rt;
        GetClientRect(hWnd, &rt);

        HDC memDC = CreateCompatibleDC(hDC);
        HBITMAP memBitmap = CreateCompatibleBitmap(
            hDC,
            rt.right,
            rt.bottom
        );
        HBITMAP oldBitmap =
            (HBITMAP)SelectObject(memDC, memBitmap);

        FillRect(memDC, &rt, (HBRUSH)GetStockObject(WHITE_BRUSH));

        VillageMap.Draw(memDC);

        Graphics graphics(memDC);

        if (VillageMap.GetCurrentMap() == MapType::Cave)
        {
            //if (oniSpawner != nullptr)
            //{
                //oniSpawner->Draw(graphics);
            //}

            //if (gumihoSpawner != nullptr)
            //{
                //gumihoSpawner->Draw(graphics);//일단 임시로 동굴에서 구미호 생성
            //}

            if (shadowSpawner != nullptr)
            {
                shadowSpawner->Draw(graphics);
            }
        }

        if (player)
        {
            player->Draw(graphics);
        }

        BitBlt(hDC, 0, 0, rt.right, rt.bottom, memDC, 0, 0, SRCCOPY);

        SelectObject(memDC, oldBitmap);
        DeleteObject(memBitmap);
        DeleteDC(memDC);

        EndPaint(hWnd, &ps);
        return 0;
    }

    case WM_TIMER:
    {
        if (wParam == 1 && player)
        {
            //const float deltaTime = 0.016f;
            QueryPerformanceCounter(&currentTime);

            float deltaTime =
                static_cast<float>(
                    currentTime.QuadPart - previousTime.QuadPart
                    )
                / static_cast<float>(frequency.QuadPart);

            previousTime = currentTime;
            //맵 이동 설정은 여기서(플레이어까지)
            player->Move(deltaTime, VillageMap);
            VillageMap.Maptransform(*player);

            InvalidateRect(hWnd, nullptr, FALSE);

            if (VillageMap.GetCurrentMap() == MapType::Cave)
            {
                //oniSpawner->Update(deltaTime, player);
                //gumihoSpawner->Update(deltaTime, player);//여기도 일단 동굴에서 생성하도록 함 임시
                shadowSpawner->Update(deltaTime, player);
            }
        }

        return 0;
    }


    case WM_DESTROY:
    {
        KillTimer(hWnd, 1);

        delete player;
        player = nullptr;

        delete oniSpawner;
        oniSpawner = nullptr;

        delete gumihoSpawner;
        gumihoSpawner = nullptr;

        delete shadowSpawner;
        shadowSpawner = nullptr;

        PostQuitMessage(0);
        return 0;
    }

    case WM_KEYDOWN:

        switch (wParam)
        {

        case VK_ESCAPE:
            PostQuitMessage(0);
            return 0;
        }
        return 0;

    }

	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}
