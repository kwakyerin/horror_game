#include <windows.h>
#include <tchar.h>
#include "Map.h"
#include "Image.h"
#include "Character.h"
#include "MonsterSpawner.h"

#pragma comment(lib, "gdiplus.lib")

Map VillageMap;

Character* player = nullptr;
MonsterSpawner* oniSpawner = nullptr;

ULONG_PTR gdiplusToken;

RECT wallRect =
{
    300,200,450,350
};

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

        player = new Character(
            L"Image\\character\\character_3_frame16x20.png"
        );

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
            const float deltaTime = 0.016f;

            player->Move(deltaTime, VillageMap); //충돌체크(맵 여기서 바꾸기)
            VillageMap.Maptransform(*player);

            InvalidateRect(hWnd, nullptr, FALSE);
        }

        return 0;
    }


    case WM_DESTROY:
    {
        KillTimer(hWnd, 1);

        delete player;
        player = nullptr;

        /*delete oniSpawner;
        oniSpawner = nullptr;*/

        PostQuitMessage(0);
        return 0;
    }

    }

	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}
