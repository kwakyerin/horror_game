#include "Map.h"
#include "Image.h"

Map::Map()
{

    currentMap = Village;

    //바닥
    for (int y = 0; y < Map_Height; y++)
    {
        for (int x = 0; x < Map_Width; x++)
        {
            map[y][x] = TILE_GRASS;
        }
    }

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

    map[10][20] = 3;
    map[11][20] = 3;

    //더미(잠시 생략)

    //작은 나무
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

    //큰 나무
    map[7][7] = TREE_01;
    map[8][7] = TREE_03;
    map[7][8] = TREE_02;
    map[8][8] = TREE_04;

    map[3][10] = TREE_01;
    map[4][10] = TREE_03;
    map[3][11] = TREE_02;
    map[4][11] = TREE_04;

    map[0][8] = TREE_01;
    map[1][8] = TREE_03;
    map[0][9] = TREE_02;
    map[1][9] = TREE_04;

    //집
    map[9][14] = 16;
    map[9][15] = 17;
    map[9][16] = 18;
    map[9][17] = 19;
    map[9][18] = 20;
    map[9][19] = 21;
    map[9][20] = 22;
    map[9][21] = 23;
    map[8][14] = 24;
    map[8][15] = 25;
    map[8][16] = 26;
    map[8][17] = 27;
    map[8][18] = 28;
    map[8][19] = 29;
    map[8][20] = 30;
    map[8][21] = 31;
    map[7][14] = 32;
    map[7][15] = 33;
    map[7][16] = 34;
    map[7][17] = 35;
    map[7][18] = 36;
    map[7][19] = 37;
    map[7][20] = 38;
    map[7][21] = 39;
    map[6][14] = 40;

    //나무 울타리

    for (int i = 19; i >=13; i--) {
        map[11][i] = Wood;
    }
    map[11][21] = Wood;
    map[11][22] = Wood;

    //꽃 풀숲
    map[11][9] = FlOWER;
    map[11][10] = FlOWER;
    map[14][20] = FlOWER;
    map[14][21] = FlOWER;

    //돌_06
    map[4][8] = ROCK_06;
}

bool Map::LoadImages()
{
    bool result = true;

    //바닥
    result &= grassImage.Load(
        L"C:\\Horror_Game\\Horror_Game\\Image\\Village\\Grass.png"
    );

    //작은 나무(위)
    result &= treeTopImage.Load(
        L"C:\\Horror_Game\\Horror_Game\\Image\\Village\\Tree_top.png"
    );

    //작은 나무(아래)
    result &= treeBottomImage.Load(
        L"C:\\Horror_Game\\Horror_Game\\Image\\Village\\Tree_bottom.png"
    );
    
    //길
    result &= roadImage.Load(
        L"C:\\Horror_Game\\Horror_Game\\Image\\Village\\Road.png"
    );

    result &= dummyImage.Load(
        L"C:\\Horror_Game\\Horror_Game\\Image\\Village\\Dummy_01.png"
    );

    //수풀
    result &= minitreeImage.Load(
        L"C:\\Horror_Game\\Horror_Game\\Image\\Village\\Grass_02.png"
    );
    
    //돌
    result &= rockImage.Load(
        L"C:\\Horror_Game\\Horror_Game\\Image\\Village\\Rock.png"
    );

    //우물
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

    //큰 나무
    result &= tree_01Image.Load(
        L"C:\\Horror_Game\\Horror_Game\\Image\\Village\\Tree_01.png"
    );
    result &= tree_02Image.Load(
        L"C:\\Horror_Game\\Horror_Game\\Image\\Village\\Tree_02.png"
    );
    result &= tree_03Image.Load(
        L"C:\\Horror_Game\\Horror_Game\\Image\\Village\\Tree_03.png"
    );
    result &= tree_04Image.Load(
        L"C:\\Horror_Game\\Horror_Game\\Image\\Village\\Tree_04.png"
    );

    //집
    result &= house_01Image.Load(
        L"C:\\Horror_Game\\Horror_Game\\Image\\Village\\House_01.png"
    );
    result &= house_02Image.Load(
        L"C:\\Horror_Game\\Horror_Game\\Image\\Village\\House_02.png"
    );
    result &= house_03Image.Load(
        L"C:\\Horror_Game\\Horror_Game\\Image\\Village\\House_03.png"
    );
    result &= house_04Image.Load(
        L"C:\\Horror_Game\\Horror_Game\\Image\\Village\\House_04.png"
    );
    result &= house_05Image.Load(
        L"C:\\Horror_Game\\Horror_Game\\Image\\Village\\House_05.png"
    );
    result &= house_06Image.Load(
        L"C:\\Horror_Game\\Horror_Game\\Image\\Village\\House_06.png"
    );
    result &= house_07Image.Load(
        L"C:\\Horror_Game\\Horror_Game\\Image\\Village\\House_07.png"
    );
    result &= house_08Image.Load(
        L"C:\\Horror_Game\\Horror_Game\\Image\\Village\\House_08.png"
    );
    result &= house_09Image.Load(
        L"C:\\Horror_Game\\Horror_Game\\Image\\Village\\House_09.png"
    );
    result &= house_10Image.Load(
        L"C:\\Horror_Game\\Horror_Game\\Image\\Village\\House_10.png"
    );
    result &= house_11Image.Load(
        L"C:\\Horror_Game\\Horror_Game\\Image\\Village\\House_11.png"
    );
    result &= house_12Image.Load(
        L"C:\\Horror_Game\\Horror_Game\\Image\\Village\\House_12.png"
    );
    result &= house_13Image.Load(
        L"C:\\Horror_Game\\Horror_Game\\Image\\Village\\House_13.png"
    );
    result &= house_14Image.Load(
        L"C:\\Horror_Game\\Horror_Game\\Image\\Village\\House_14.png"
    );
    result &= house_15Image.Load(
        L"C:\\Horror_Game\\Horror_Game\\Image\\Village\\House_15.png"
    );
    result &= house_16Image.Load(
        L"C:\\Horror_Game\\Horror_Game\\Image\\Village\\House_16.png"
    );
    result &= house_17Image.Load(
        L"C:\\Horror_Game\\Horror_Game\\Image\\Village\\House_17.png"
    );
    result &= house_18Image.Load(
        L"C:\\Horror_Game\\Horror_Game\\Image\\Village\\House_18.png"
    );
    result &= house_19Image.Load(
        L"C:\\Horror_Game\\Horror_Game\\Image\\Village\\House_19.png"
    );
    result &= house_20Image.Load(
        L"C:\\Horror_Game\\Horror_Game\\Image\\Village\\House_20.png"
    );
    result &= house_21Image.Load(
        L"C:\\Horror_Game\\Horror_Game\\Image\\Village\\House_21.png"
    );
    result &= house_22Image.Load(
        L"C:\\Horror_Game\\Horror_Game\\Image\\Village\\House_22.png"
    );
    result &= house_23Image.Load(
        L"C:\\Horror_Game\\Horror_Game\\Image\\Village\\House_23.png"
    );
    result &= house_24Image.Load(
        L"C:\\Horror_Game\\Horror_Game\\Image\\Village\\House_24.png"
    );
    result &= house_25Image.Load(
        L"C:\\Horror_Game\\Horror_Game\\Image\\Village\\House_25.png"
    );
    result &= house_26Image.Load(
        L"C:\\Horror_Game\\Horror_Game\\Image\\Village\\House_26.png"
    );
    result &= house_27Image.Load(
        L"C:\\Horror_Game\\Horror_Game\\Image\\Village\\House_27.png"
    );
    result &= house_28Image.Load(
        L"C:\\Horror_Game\\Horror_Game\\Image\\Village\\House_28.png"
    );
    result &= house_29Image.Load(
        L"C:\\Horror_Game\\Horror_Game\\Image\\Village\\House_29.png"
    );
    result &= house_30Image.Load(
        L"C:\\Horror_Game\\Horror_Game\\Image\\Village\\House_30.png"
    );

    //울타리
    result &= woodImage.Load(
        L"C:\\Horror_Game\\Horror_Game\\Image\\Village\\Wood.png"
    );

    //꽃
    result &= flowerImage.Load(
        L"C:\\Horror_Game\\Horror_Game\\Image\\Village\\Grass_03.png"
    );

    //돌(2 버전)
    result &= rock_06Image.Load(
        L"C:\\Horror_Game\\Horror_Game\\Image\\Village\\Rock_06.png"
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

            case TREE_01:
                grassImage.Draw(hdc, drawX, drawY);
                tree_01Image.Draw(hdc, drawX, drawY);
                break;

            case TREE_02:
                grassImage.Draw(hdc, drawX, drawY);
                tree_02Image.Draw(hdc, drawX, drawY);
                break;

            case TREE_03:
                grassImage.Draw(hdc, drawX, drawY);
                tree_03Image.Draw(hdc, drawX, drawY);
                break;

            case TREE_04:
                grassImage.Draw(hdc, drawX, drawY);
                tree_04Image.Draw(hdc, drawX, drawY);
                break;

            case House_01:
                grassImage.Draw(hdc, drawX, drawY);
                house_01Image.Draw(hdc, drawX, drawY);
                break;

            case House_02:
                grassImage.Draw(hdc, drawX, drawY);
                house_02Image.Draw(hdc, drawX, drawY);
                break;

            case House_03:
                grassImage.Draw(hdc, drawX, drawY);
                house_03Image.Draw(hdc, drawX, drawY);
                break;

            case House_04:
                grassImage.Draw(hdc, drawX, drawY);
                house_04Image.Draw(hdc, drawX, drawY);
                break;

            case House_05:
                grassImage.Draw(hdc, drawX, drawY);
                house_05Image.Draw(hdc, drawX, drawY);
                break;

            case House_06:
                grassImage.Draw(hdc, drawX, drawY);
                house_06Image.Draw(hdc, drawX, drawY);
                break;

            case House_07:
                grassImage.Draw(hdc, drawX, drawY);
                house_07Image.Draw(hdc, drawX, drawY);
                break;

            case House_08:
                grassImage.Draw(hdc, drawX, drawY);
                house_08Image.Draw(hdc, drawX, drawY);
                break;

            case House_09:
                grassImage.Draw(hdc, drawX, drawY);
                house_09Image.Draw(hdc, drawX, drawY);
                break;

            case House_10:
                grassImage.Draw(hdc, drawX, drawY);
                house_10Image.Draw(hdc, drawX, drawY);
                break;
            case House_11:
                grassImage.Draw(hdc, drawX, drawY);
                house_11Image.Draw(hdc, drawX, drawY);
                break;
            case House_12:
                grassImage.Draw(hdc, drawX, drawY);
                house_12Image.Draw(hdc, drawX, drawY);
                break;

            case House_13:
                grassImage.Draw(hdc, drawX, drawY);
                house_13Image.Draw(hdc, drawX, drawY);
                break;

            case House_14:
                grassImage.Draw(hdc, drawX, drawY);
                house_14Image.Draw(hdc, drawX, drawY);
                break;

            case House_15:
                grassImage.Draw(hdc, drawX, drawY);
                house_15Image.Draw(hdc, drawX, drawY);
                break;

            case House_16:
                grassImage.Draw(hdc, drawX, drawY);
                house_16Image.Draw(hdc, drawX, drawY);
                break;

            case House_17:
                grassImage.Draw(hdc, drawX, drawY);
                house_17Image.Draw(hdc, drawX, drawY);
                break;

            case House_18:
                grassImage.Draw(hdc, drawX, drawY);
                house_18Image.Draw(hdc, drawX, drawY);
                break;

            case House_19:
                grassImage.Draw(hdc, drawX, drawY);
                house_19Image.Draw(hdc, drawX, drawY);
                break;

            case House_20:
                grassImage.Draw(hdc, drawX, drawY);
                house_20Image.Draw(hdc, drawX, drawY);
                break;

            case House_21:
                grassImage.Draw(hdc, drawX, drawY);
                house_21Image.Draw(hdc, drawX, drawY);
                break;

            case House_22:
                grassImage.Draw(hdc, drawX, drawY);
                house_22Image.Draw(hdc, drawX, drawY);
                break;

            case House_23:
                grassImage.Draw(hdc, drawX, drawY);
                house_23Image.Draw(hdc, drawX, drawY);
                break;
            case House_24:
                grassImage.Draw(hdc, drawX, drawY);
                house_24Image.Draw(hdc, drawX, drawY);
                break;
            case House_25:
                grassImage.Draw(hdc, drawX, drawY);
                house_25Image.Draw(hdc, drawX, drawY);
                break;
            case House_26:
                grassImage.Draw(hdc, drawX, drawY);
                house_26Image.Draw(hdc, drawX, drawY);
                break;
            case House_27:
                grassImage.Draw(hdc, drawX, drawY);
                house_27Image.Draw(hdc, drawX, drawY);
                break;
            case House_28:
                grassImage.Draw(hdc, drawX, drawY);
                house_28Image.Draw(hdc, drawX, drawY);
                break;
            case House_29:
                grassImage.Draw(hdc, drawX, drawY);
                house_29Image.Draw(hdc, drawX, drawY);
                break;
            case House_30:
                grassImage.Draw(hdc, drawX, drawY);
                house_30Image.Draw(hdc, drawX, drawY);
                break;

            case Wood:
                grassImage.Draw(hdc, drawX, drawY);
                woodImage.Draw(hdc, drawX, drawY);
                break;

            case FlOWER:
                grassImage.Draw(hdc, drawX, drawY);
                flowerImage.Draw(hdc, drawX, drawY);
                break;
                
            case ROCK_06:
                grassImage.Draw(hdc, drawX, drawY);
                rock_06Image.Draw(hdc, drawX, drawY);
                break;
            }
        }
    }
}

void Map::changeMap(MapType newMap)
{
}
