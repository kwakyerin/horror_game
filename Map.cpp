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
}

bool Map::LoadImages()
{
    bool result = true;

    result &= grassImage.Load(
        L"C:\\Horror_Game\\Horror_Game\\Image\\Village\\Grass.png"
    );

    /*
    result &= treeTopImage.Load(
        L"C:\\Horror_Game\\Horror_Game\\Image\\Village\\TreeTop.png"
    );

    result &= treeMiddleImage.Load(
        L"C:\\Horror_Game\\Horror_Game\\Image\\Village\\TreeMiddle.png"
    );

    result &= treeBottomImage.Load(
        L"C:\\Horror_Game\\Horror_Game\\Image\\Village\\TreeBottom.png"
    );

    result &= roadImage.Load(
        L"C:\\Horror_Game\\Horror_Game\\Image\\Village\\Road.png"
    );
    */

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

            case TILE_TREE_MIDDLE:
                grassImage.Draw(hdc, drawX, drawY);
                treeMiddleImage.Draw(hdc, drawX, drawY);
                break;

            case TILE_TREE_BOTTOM:
                grassImage.Draw(hdc, drawX, drawY);
                treeBottomImage.Draw(hdc, drawX, drawY);
                break;

            case TILE_ROAD:
                roadImage.Draw(hdc, drawX, drawY);
                break;
            }
        }
    }
}