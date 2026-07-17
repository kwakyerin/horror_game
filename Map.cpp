#include "Map.h"
#include "Image.h"

Map::Map()
{
    for (int y = 0; y < Map_Height; y++)
    {
        for (int x = 0; x < Map_Width; x++)
        {
            map[y][x] = TILE_GRASS;
        }
    }

    // 나무가 세로 3칸일 경우
    /*
    map[3][5] = TILE_TREE_TOP;
    map[4][5] = TILE_TREE_MIDDLE;
    map[5][5] = TILE_TREE_BOTTOM;
    */


    //길

    for (int i = 4; i < 6; i++) {
        for (int j = 0; j < 5; j++) {
            map[i][j] = TILE_ROAD;
        }
    }

    for (int i = 0; i < 18; i++) {
        for (int j = 5; j < 7; j++) {
            map[i][j] = TILE_ROAD;
        }
    }

    for (int i = 12; i < 14; i++) {
        for (int j = 7; j < 25; j++) {
            map[i][j] = TILE_ROAD;
        }
    }

    //더미(잠시 생략)

    //나무
    map[2][1] = 1;
    map[3][1] = 2;

    map[10][8] = 1;
    map[11][8] = 2;

    map[13][4] = 1;
    map[14][4] = 2;

    //풀숲
    map[3][3] = TILE_MINITREE;
    map[3][4] = TILE_MINITREE;
    map[2][4] = TILE_MINITREE;
    map[6][2] = TILE_MINITREE;
    map[6][3] = TILE_MINITREE;

    map[14][11] = TILE_MINITREE;
    map[14][13] = TILE_MINITREE;
    map[14][14] = TILE_MINITREE;

    //돌
    map[8][0] = TILE_ROCK;
    map[9][1] = TILE_ROCK;
    map[16][4] = TILE_ROCK;

    //우물
    map[8][9] = WELL_01;
    map[8][10] = WELL_02;
    map[9][9] = WELL_03;
    map[9][10] = WELL_04;
}

bool Map::LoadImages()
{
    bool result = true;

    result &= grassImage.Load(
        L"C:\\Horror_Game\\Horror_Game\\Image\\Village\\Grass.png"
    );

    
    result &= treeTopImage.Load(
        L"C:\\Horror_Game\\Horror_Game\\Image\\Village\\Tree_top.png"
    );

    result &= treeBottomImage.Load(
        L"C:\\Horror_Game\\Horror_Game\\Image\\Village\\Tree_bottom.png"
    );
    
    result &= roadImage.Load(
        L"C:\\Horror_Game\\Horror_Game\\Image\\Village\\Road.png"
    );

    result &= dummyImage.Load(
        L"C:\\Horror_Game\\Horror_Game\\Image\\Village\\Dummy_01.png"
    );

    result &= minitreeImage.Load(
        L"C:\\Horror_Game\\Horror_Game\\Image\\Village\\Grass_02.png"
    );
    
    result &= rockImage.Load(
        L"C:\\Horror_Game\\Horror_Game\\Image\\Village\\Rock.png"
    );

    result &= well_01Image.Load(
        L"C:\\Horror_Game\\Horror_Game\\Image\\Village\\Well_01.png"
    );
    result &= well_02Image.Load(
        L"C:\\Horror_Game\\Horror_Game\\Image\\Village\\Well_02.png"
    );
    result &= well_03Image.Load(
        L"C:\\Horror_Game\\Horror_Game\\Image\\Village\\Well_03.png"
    );
    result &= well_04Image.Load(
        L"C:\\Horror_Game\\Horror_Game\\Image\\Village\\Well_04.png"
    );

    return result;
}

void Map::Draw(HDC hdc)
{
    for (int y = 0; y < Map_Height; y++)
    {
        for (int x = 0; x < Map_Width; x++)
        {
            int drawX = x * Tile_Size;
            int drawY = y * Tile_Size;

            switch (map[y][x])
            {
            case TILE_GRASS:
                grassImage.Draw(hdc, drawX, drawY);
                break;

            case TILE_TREE_TOP:
                grassImage.Draw(hdc, drawX, drawY);
                treeTopImage.Draw(hdc, drawX, drawY);
                break;

            case TILE_TREE_BOTTOM:
                grassImage.Draw(hdc, drawX, drawY);
                treeBottomImage.Draw(hdc, drawX, drawY);
                break;

            case TILE_ROAD:
                roadImage.Draw(hdc, drawX, drawY);
                break;

            case TILE_DUMMY:
                grassImage.Draw(hdc, drawX, drawY);
                dummyImage.Draw(hdc, drawX, drawY);
                break;

            case TILE_MINITREE:
                grassImage.Draw(hdc, drawX, drawY);
                minitreeImage.Draw(hdc, drawX, drawY);
                break;

            case TILE_ROCK:
                grassImage.Draw(hdc, drawX, drawY);
                rockImage.Draw(hdc, drawX, drawY);
                break;

            case WELL_01:
                grassImage.Draw(hdc, drawX, drawY);
                well_01Image.Draw(hdc, drawX, drawY);
                break;

            case WELL_02:
                grassImage.Draw(hdc, drawX, drawY);
                well_02Image.Draw(hdc, drawX, drawY);
                break;

            case WELL_03:
                grassImage.Draw(hdc, drawX, drawY);
                well_03Image.Draw(hdc, drawX, drawY);
                break;

            case WELL_04:
                grassImage.Draw(hdc, drawX, drawY);
                well_04Image.Draw(hdc, drawX, drawY);
                break;
            }
        }
    }
}