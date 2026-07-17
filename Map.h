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
    TILE_TREE_BOTTOM,
    TILE_ROAD,
    TILE_DUMMY,
    TILE_MINITREE,
    TILE_ROCK,
    WELL_01,
    WELL_02,
    WELL_03,
    WELL_04
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

    GameImage treeTopImage;
    GameImage treeBottomImage;
    GameImage roadImage;
    GameImage dummyImage;
    GameImage minitreeImage;
    GameImage rockImage;
    GameImage well_01Image;
    GameImage well_02Image;
    GameImage well_03Image;
    GameImage well_04Image;
};