#pragma once

#include <Windows.h>
#include "Image.h"

const int Map_Width = 25;
const int Map_Height = 18;
const int Tile_Size = 32;

enum TileType
{
    TILE_GRASS = 0,
    TILE_TREE_TOP,
    TILE_TREE_MIDDLE,
    TILE_TREE_BOTTOM,
    TILE_ROAD
};

class Map
{
public:
    Map();

    bool LoadImages();
    void Draw(HDC hdc);

private:
    int map[Map_Height][Map_Width];

    GameImage grassImage;

    //이미지 추가할 때 동시에 사용
    GameImage treeTopImage;
    GameImage treeMiddleImage;
    GameImage treeBottomImage;
    GameImage roadImage;
};