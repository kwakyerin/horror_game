#include <vector>
#include <windows.h>
#include <tchar.h>
#include <cstdlib>
#include <ctime>
#include "Map.h"
#include "Image.h"
#include "Character.h"
#include "MonsterSpawner.h"
#include "Gumiho.h"
#include "ShadowGhost.h"
#include "kkamakGhost.h"
#include "TitleScreen.h"
#include "EndScreen.h"
#include "QuizGhost.h"
#include "Dialogue.h"
#include "npc.h"
#include "UI.h"
#include "ResetGame.h"
#include "Amulet.h"
#include "DayNightManager.h"


#pragma comment(lib, "gdiplus.lib")


TitleScreen* titleScreen = nullptr;//타이틀 시작화면
EndScreen* endScreen = nullptr;
enum class GameState
{
    Title,
    Playing,
    End
};
std::vector<Amulet> amulets;
GameState gameState = GameState::Playing;//상태 바꾸려면 여기서 바꾸면 된다.

Map VillageMap;

Dialogue dialogue;
NPC npcManager;

UI* ui = nullptr;

DayNightManager dayNight; //밤 낮 조정
bool introDialoguePlayed = false;

Character* player = nullptr;
MonsterSpawner* oniSpawner = nullptr;
MonsterSpawner* gumihoSpawner = nullptr;
MonsterSpawner* shadowSpawner = nullptr;

KkamakGhost* kkamakGhost = nullptr;//따라오게만 할거라서 스포너로 안함
QuizGhost* quizGhost = nullptr;

ULONG_PTR gdiplusToken;

RECT wallRect =
{
    300,200,450,350
};

LARGE_INTEGER frequency;
LARGE_INTEGER previousTime;
LARGE_INTEGER currentTime;

//버벅거림 해결변수
HDC g_mapDC = nullptr;
HBITMAP g_mapBitmap = nullptr;
HBITMAP g_oldMapBitmap = nullptr;
//여기까지

HINSTANCE g_hInst;
LPCTSTR lpszClass = L"OBU_Project";
LPCTSTR lpszWindowName = L"OBU_Project";
LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam);

void CreateMapBuffer(HWND hWnd)
{
    HDC hdc = GetDC(hWnd);

    if (g_mapDC != nullptr)
    {
        SelectObject(g_mapDC, g_oldMapBitmap);
        DeleteObject(g_mapBitmap);
        DeleteDC(g_mapDC);

        g_mapDC = nullptr;
        g_mapBitmap = nullptr;
        g_oldMapBitmap = nullptr;
    }

    const int mapPixelWidth = Map_Width * Tile_Size;
    const int mapPixelHeight = Map_Height * Tile_Size;

    g_mapDC = CreateCompatibleDC(hdc);

    g_mapBitmap = CreateCompatibleBitmap(
        hdc,
        mapPixelWidth,
        mapPixelHeight
    );

    g_oldMapBitmap = static_cast<HBITMAP>(
        SelectObject(g_mapDC, g_mapBitmap)
        );

    // 중요: 비트맵 전체를 먼저 초기화
    RECT mapRect =
    {
        0,
        0,
        mapPixelWidth,
        mapPixelHeight
    };

    FillRect(
        g_mapDC,
        &mapRect,
        static_cast<HBRUSH>(GetStockObject(WHITE_BRUSH))
    );

    VillageMap.Draw(g_mapDC);

    ReleaseDC(hWnd, hdc);
}

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

    hWnd = CreateWindow(lpszClass,lpszWindowName,WS_OVERLAPPEDWINDOW,0,0,800,600,nullptr,nullptr,hInstance,nullptr);

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

        titleScreen = new TitleScreen();
        titleScreen->LoadImages();

        endScreen = new EndScreen();
        endScreen->LoadImages();

       
        ui = new UI();
        ui->LoadImages();

        if (!VillageMap.LoadImages())
        {
            // MessageBox(hWnd, L"맵 이미지 로드 실패", L"Error", MB_OK);
        }

        CreateMapBuffer(hWnd); //버벅거림 해결코드

        //비 효과 그리기
        srand((unsigned int)time(nullptr));

        VillageMap.InitEffect(
            Map_Width * Tile_Size,
            Map_Height * Tile_Size
        );

        VillageMap.SetRainEnabled(true);   // 일단 테스트용으로 항상 비

        //플레이어 설정
        player = new Character(L"Image\\character\\character_3_frame16x20.png");
        //부적위치
        amulets.emplace_back(Cave_02,12*Tile_Size,9*Tile_Size, AmuletType::Yellow);//동굴 조각상 왼쪽 아래 발 부분
        amulets.emplace_back(Market, 14 * Tile_Size, 4 * Tile_Size, AmuletType::Red);//시장 오른쪽 테이블 밑
        amulets.emplace_back(Govillage, 2 * Tile_Size, 3 * Tile_Size, AmuletType::Blue);//마을 가는 길 가장 안쪽에 긴 나무 
        amulets.emplace_back(Room, 14 * Tile_Size, 5 * Tile_Size, AmuletType::White);//집 항아리
        amulets.emplace_back(Room, 14 * Tile_Size, 5 * Tile_Size, AmuletType::Black);//아직 수정해야함

        oniSpawner = new MonsterSpawner(MonsterType::Oni,
            15 * Tile_Size,   // 타일 X = 15 (큰 크리스탈 쪽으로 가까이 가면 뜸)
            6 * Tile_Size,    // 타일 Y = 6
            100.0f,    // 플레이어가 400 안으로 오면 생성
            250.0f,    // 몬스터 탐지 범위
            80.0f,     // 몬스터 공격 범위
            L"Image\\monster_oni\\Walk.png",
            L"Image\\monster_oni\\Attack.png"
        );

        gumihoSpawner = new MonsterSpawner(MonsterType::Gumiho, 16 * Tile_Size, 3 * Tile_Size, 100.0f, 600.0f, 300.0f,
            L"Image\\monster_gumiho\\Run.png",
            L"Image\\monster_gumiho\\Attack.png");// 구미호 위치도 임시

        shadowSpawner = new MonsterSpawner(MonsterType::ShadowGhost, 14 * Tile_Size, 3 * Tile_Size, 100.0f, 0.0f, 0.0f,
            L"Image\\monster_shadow\\warning.png",
            L"Image\\monster_shadow\\attack.png");//그림자 귀신도 임시

        kkamakGhost = new KkamakGhost(9 * Tile_Size, 3 * Tile_Size, L"Image\\monster_kkamak\\kkamak.png");//까막 귀신도 임시

        quizGhost = new QuizGhost(14 * Tile_Size, 6 * Tile_Size, L"Image\\monster_quiz\\quiz_ghost.png");

        QueryPerformanceFrequency(&frequency);
        QueryPerformanceCounter(&previousTime);

        SetTimer(hWnd, 1, 20, nullptr);

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

        VillageMap.InitEffect(
            Map_Width * Tile_Size,
            Map_Height * Tile_Size
        );

        VillageMap.SetRainEnabled(true);

        Graphics graphics(memDC);

        switch (gameState) {
        case GameState::Title: {
            titleScreen->Draw(graphics);
            break;
        }

        case GameState::Playing: {

            //느려짐해결코드
            BitBlt(
                memDC,
                0,
                0,
                Map_Width * Tile_Size,
                Map_Height * Tile_Size,
                g_mapDC,
                0,
                0,
                SRCCOPY
            );
            if (dayNight.IsNight()) {

                if (VillageMap.GetCurrentMap() == MapType::Cave)
                {
                    if (oniSpawner != nullptr)
                    {
                        oniSpawner->Draw(graphics);
                    }
                }

                if (VillageMap.GetCurrentMap() == MapType::Gotemple_01)
                {
                    if (gumihoSpawner != nullptr)
                    {
                        gumihoSpawner->Draw(graphics);
                    }
                }

                if (VillageMap.GetCurrentMap() == MapType::Govillage)
                {
                    if (kkamakGhost != nullptr)
                    {
                        kkamakGhost->Draw(graphics);
                    }
                }

                if (VillageMap.GetCurrentMap() == MapType::Gomarket_02)
                {
                    if (quizGhost != nullptr)
                    {
                        quizGhost->Draw(graphics);
                    }
                }

                if (VillageMap.GetCurrentMap() == MapType::Field)
                {
                    if (shadowSpawner != nullptr)
                    {
                        shadowSpawner->Draw(graphics);
                    }
                }
            }//밤-몬스터 설정

            if (player)
            {
                player->Draw(graphics);
            }


            MapType currentMap = VillageMap.GetCurrentMap();

            if (currentMap != MapType::Cave &&
                currentMap != MapType::Cave_02 &&
                currentMap != MapType::Room)
            {
                VillageMap.DrawEffect(graphics);
            }

            dialogue.Draw(graphics, rt.right, rt.bottom);

            SolidBrush darkBrush(Color(80, 0, 0, 0));

            graphics.FillRectangle(&darkBrush,0,0,rt.right,rt.bottom);

            ui->Draw(graphics, player, amulets,VillageMap.GetCurrentMap());//부적이랑 하트

            break;
        }
        case GameState::End: {
            endScreen->Draw(graphics);
            break;
        }

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
        if (wParam == 1)
        {
            QueryPerformanceCounter(&currentTime);

            float deltaTime =
                static_cast<float>(currentTime.QuadPart - previousTime.QuadPart)
                / static_cast<float>(frequency.QuadPart);

            previousTime = currentTime;

            if (deltaTime > 0.033f)
            {
                deltaTime = 0.033f;
            }

            if (gameState == GameState::Title)
            {
                if (titleScreen != nullptr)
                {
                    titleScreen->Update(deltaTime);
                }
                InvalidateRect(hWnd, nullptr, FALSE);
            }

            else if (gameState == GameState::Playing && player)
            {
                std::vector <::RECT> obstacleRects;

                //시작 설명창
                if (!introDialoguePlayed)
                {
                    dialogue.Open(
                        {
                            L"내 이름은 곽진아",
                            L"귀신을 물리치는 퇴마사다.",
                            L"오늘은 이 수상해보이는 마을에 요괴를 물리쳐달라는 의뢰를 받고 비를 뚫고 여기까지 왔다.",
                            L"이 마을에 사는 주민같이 보이시는 분이 이런 허름한 집으로 안내했다.",
                            L"집에서 퀴퀴한 게 냄새가 나군..",
                            L"아직 의뢰인을 만나지 못한 상태다.",
                            L"사찰로 가는 길에서 만나자고 하셨는데...",
                            L"일단 마을을 벗어나서 사찰로 한 번 가볼까..?",
                        });

                    introDialoguePlayed = true;
                }

                if (VillageMap.GetCurrentMap() == MapType::Cave)
                {
                    oniSpawner->Update(deltaTime, player);                   
                }

                if (VillageMap.GetCurrentMap() == MapType::Gotemple_01)
                {
                    gumihoSpawner->Update(deltaTime, player);
                }

                if (VillageMap.GetCurrentMap() == MapType::Govillage)
                {
                    if (kkamakGhost->Update(deltaTime, *player))
                    {
                       // player->Damage(player->GetHP());
                    }
                }

                if (VillageMap.GetCurrentMap() == MapType::Field)
                {
                    shadowSpawner->Update(deltaTime, player);
                }

                if (VillageMap.GetCurrentMap() == MapType::Gomarket_02)
                {
                    quizGhost->Update(deltaTime, *player);
                    obstacleRects.push_back(quizGhost->GetCollisionRect());

                }


                //비 오는 효과
                MapType currentMap = VillageMap.GetCurrentMap();

                if (currentMap != MapType::Cave &&
                    currentMap != MapType::Cave_02 &&
                    currentMap != MapType::Room)
                {
                    VillageMap.UpdateEffect(
                        Map_Width * Tile_Size,
                        Map_Height * Tile_Size
                    );
                }

                //퀴즈요괴 밤 설정
                bool canMove = true;

               // 대화 중에는 이동 불가
                if (dialogue.IsOpen())
                {
                    canMove = false;
                }

                // 퀴즈 중에도 이동 불가
                if (dayNight.IsNight() &&
                    quizGhost != nullptr &&
                    quizGhost->IsQuizActive())
                {
                    canMove = false;
                }

                if (canMove)
                {
                    player->Move(
                        deltaTime,
                        VillageMap,
                        obstacleRects
                    );
                }

                MapType previousMap = VillageMap.GetCurrentMap();

                VillageMap.Maptransform(*player);


                if (previousMap != VillageMap.GetCurrentMap())
                {
                    CreateMapBuffer(hWnd);
                }
                player->UpdateDeath(deltaTime);

                // 죽음 애니메이션이 끝나면 End 화면
                if (player->IsDeathAnimationFinished())
                {
                    gameState = GameState::End;
                }
                 

                InvalidateRect(hWnd, nullptr, FALSE);
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

        delete kkamakGhost;
        kkamakGhost = nullptr;

        delete quizGhost;
        quizGhost = nullptr;

        delete titleScreen;
        titleScreen = nullptr;

        delete endScreen;
        endScreen = nullptr;

        delete ui;
        ui = nullptr;

        if (g_mapDC != nullptr)
        {
            SelectObject(g_mapDC, g_oldMapBitmap);
            DeleteObject(g_mapBitmap);
            DeleteDC(g_mapDC);

            g_mapDC = nullptr;
            g_mapBitmap = nullptr;
            g_oldMapBitmap = nullptr;
        }

        PostQuitMessage(0);
        return 0;
    }

    case WM_KEYDOWN:
    {
        switch (wParam)
        {
        case VK_ESCAPE:
        {
            PostQuitMessage(0);
            return 0;
        }

        case 'W':
        {
            if (gameState == GameState::Playing &&
                quizGhost != nullptr &&
                quizGhost->IsSelecting())
            {
                quizGhost->MoveSelectionUp();

                InvalidateRect(
                    hWnd,
                    nullptr,
                    FALSE
                );

                return 0;
            }

            break;
        }
        //밤낮 테스트용 키
        case 'N':
        {
            dayNight.Toggle();

            if (dayNight.IsDay())
            {
                if (oniSpawner != nullptr)
                    oniSpawner->Reset();

                if (gumihoSpawner != nullptr)
                    gumihoSpawner->Reset();

                if (shadowSpawner != nullptr)
                    shadowSpawner->Reset();

                if (quizGhost != nullptr)
                    quizGhost->SetVisible(false);
            }
            else
            {
                if (quizGhost != nullptr)
                    quizGhost->SetVisible(true);
            }

            InvalidateRect(hWnd, nullptr, FALSE);
            return 0;
        }

        case 'S':
        {
            if (gameState == GameState::Playing &&
                quizGhost != nullptr &&
                quizGhost->IsSelecting())
            {
                quizGhost->MoveSelectionDown();

                InvalidateRect(
                    hWnd,
                    nullptr,
                    FALSE
                );

                return 0;
            }

            break;
        }

        case 'K':
        {
            if (gameState != GameState::Playing)
            {
                return 0;
            }

            // 대화창이 열려 있으면 다음 문장
            if (dialogue.IsOpen())
            {
                dialogue.Next();

                InvalidateRect(
                    hWnd,
                    nullptr,
                    FALSE
                );

                return 0;
            }
            // 숨겨진 부적 상호작용
            if (player != nullptr)
            {
                for (Amulet& amulet : amulets)
                {
                    if (amulet.Interact(
                        player,
                        VillageMap.GetCurrentMap()
                    ))
                    {
                        InvalidateRect(
                            hWnd,
                            nullptr,
                            FALSE
                        );

                        return 0;
                    }
                }
            }

            // NPC 대화
            if (player != nullptr)
            {
                int nearbyNPC =
                    VillageMap.GetNearbyNPC(
                        player->GetX(),
                        player->GetY(),
                        32,
                        32
                    );

                if (nearbyNPC != -1)
                {
                    npcManager.Talk(
                        nearbyNPC,
                        dialogue
                    );

                    InvalidateRect(
                        hWnd,
                        nullptr,
                        FALSE
                    );

                    return 0;
                }
            }

            // 퀴즈요괴 상호작용
            if (player != nullptr &&
                quizGhost != nullptr &&
                dayNight.IsNight() &&
                VillageMap.GetCurrentMap() == MapType::Gomarket_02 &&
                quizGhost->IsPlayerNear(*player))
            {
                quizGhost->HandleInteraction(
                    *player,
                    dialogue
                );

                InvalidateRect(
                    hWnd,
                    nullptr,
                    FALSE
                );

                return 0;
            }

            return 0;
        }
        }

        InvalidateRect(hWnd, nullptr, FALSE);
        return 0;
    }

    case WM_MOUSEMOVE:
    {
        POINT pt;
        pt.x = LOWORD(lParam);
        pt.y = HIWORD(lParam);
        if (gameState == GameState::Title)
        {

            titleScreen->UpdateHover(pt.x, pt.y);

            InvalidateRect(hWnd, nullptr, FALSE);


        }
        else if (gameState == GameState::End && endScreen)
        {
            endScreen->UpdateHover(pt.x, pt.y);
        }
        InvalidateRect(hWnd, nullptr, FALSE);
        return 0;
    }

    case WM_LBUTTONDOWN:
    {
        POINT pt;
        pt.x = LOWORD(lParam);
        pt.y = HIWORD(lParam);
        if (gameState == GameState::Title)
        {
            if (titleScreen->IsStartClicked(pt.x, pt.y))
            {
                ResetGame();
                CreateMapBuffer(hWnd);
                
                gameState = GameState::Playing;

                introDialoguePlayed = false;
            }


            if (titleScreen->IsExitClicked(pt.x, pt.y))
            {
                PostQuitMessage(0);
            }
        }
        else if (gameState == GameState::End)
        {
            if (endScreen->IsRetryClicked(pt.x, pt.y))
            {
                gameState = GameState::Title;
            }
            else if (endScreen->IsExitClicked(pt.x, pt.y))
            {
                PostQuitMessage(0);
            }
        }

        return 0;
    }


    }

    return DefWindowProc(hWnd, uMsg, wParam, lParam);
}