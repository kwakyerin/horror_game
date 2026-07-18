#include <windows.h>
#include <gdiplus.h>
#include "Character.h"

#pragma comment(lib, "gdiplus.lib")

using namespace Gdiplus;

Character* player = nullptr;
ULONG_PTR gdiplusToken;

RECT wallRect =
{
	300,200,450,350
}; //테스트용 벽

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_CREATE:
	{
		player = new Character(L"images\\character\\character_3_frame16x20.png");
		return 0;
	}

	case WM_PAINT:
	{
		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(hwnd, &ps);

		RECT clientRect;
		GetClientRect(hwnd, &clientRect);

		int width = clientRect.right - clientRect.left;
		int height = clientRect.bottom - clientRect.top;

		// 화면과 호환되는 메모리 DC 생성
		HDC memoryDC = CreateCompatibleDC(hdc);

		// 메모리 DC에서 사용할 비트맵 생성
		HBITMAP backBuffer = CreateCompatibleBitmap(hdc, width, height);

		// 메모리 DC에 비트맵 연결
		HBITMAP oldBitmap =
			static_cast<HBITMAP>(SelectObject(memoryDC, backBuffer));

		// 메모리 화면의 배경을 먼저 지움
		FillRect(
			memoryDC,
			&clientRect,
			reinterpret_cast<HBRUSH>(COLOR_WINDOW + 1)
		);

		// GDI+는 메모리 DC에 그림
		Gdiplus::Graphics graphics(memoryDC);

		if (player)
		{
			player->Draw(graphics);
		}

		Gdiplus::Pen wallPen(
			Gdiplus::Color(255, 0, 0, 255),
			2
		);

		graphics.DrawRectangle(
			&wallPen,
			static_cast<INT>(wallRect.left),
			static_cast<INT>(wallRect.top),
			static_cast<INT>(wallRect.right - wallRect.left),
			static_cast<INT>(wallRect.bottom - wallRect.top)
		);

		// 완성된 메모리 화면을 실제 창으로 한 번에 복사
		BitBlt(
			hdc,
			0,
			0,
			width,
			height,
			memoryDC,
			0,
			0,
			SRCCOPY
		);


		SelectObject(memoryDC, oldBitmap);
		DeleteObject(backBuffer);
		DeleteDC(memoryDC);

		EndPaint(hwnd, &ps);
		return 0;
	}
	case WM_DESTROY:
	{
		delete player;
		player = nullptr;

		PostQuitMessage(0);
		return 0;
	}
	}

	return DefWindowProc(hwnd, msg, wParam, lParam);
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE, LPSTR, int nCmdShow)
{
	GdiplusStartupInput gdiplusStartupInput;
	GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, nullptr);
	WNDCLASS wc = {};

	wc.lpfnWndProc = WndProc;
	wc.hInstance = hInstance;
	wc.lpszClassName = TEXT("MyWindow");
	wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);

	RegisterClass(&wc);

	HWND hwnd = CreateWindow(TEXT("MyWindow"), TEXT("게임화면"), WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT,
		755, 600, NULL, NULL, hInstance, NULL);

	ShowWindow(hwnd, nCmdShow);
	UpdateWindow(hwnd);

	LARGE_INTEGER frequency;
	LARGE_INTEGER previousTime;
	LARGE_INTEGER currentTime;


	float deltaTime = 0.0f;

	QueryPerformanceFrequency(&frequency);

	// 게임 시작 시각 저장
	QueryPerformanceCounter(&previousTime);

	MSG msg = {};

	while (msg.message != WM_QUIT)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else
		{
			QueryPerformanceCounter(&currentTime);

			// 이전 프레임부터 현재 프레임까지 걸린 시간
			deltaTime =
				static_cast<float>(
					currentTime.QuadPart - previousTime.QuadPart
					)
				/ static_cast<float>(frequency.QuadPart);

			// 다음 프레임 계산을 위해 현재 시간을 이전 시간으로 저장
			previousTime = currentTime;

			if (player != nullptr)
			{
				float oldX = player->GetX();
				float oldY = player->GetY();
				player->Move(deltaTime);

				RECT playerRect = player->GetCollisionRect();
				RECT result;

				if (IntersectRect(&result, &playerRect, &wallRect))
				{
					player->SetPosition(oldX, oldY);
				}
			}

			// 화면 다시 그리기 요청
			InvalidateRect(hwnd, nullptr, FALSE);
		
		}
	}
	GdiplusShutdown(gdiplusToken);

	return (int)msg.wParam;
}