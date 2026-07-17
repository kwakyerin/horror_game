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
    WELL_04,
    TREE_01,
    TREE_02,
    TREE_03,
    TREE_04,
};

class Map
{
public:
    Map();

    bool LoadImages();
    void Draw(HDC hdc);

private:
    int map[Map_Height][Map_Width];


    //마을 이미지
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

    GameImage tree_01Image;
    GameImage tree_02Image;
    GameImage tree_03Image;
    GameImage tree_04Image;

    //마을 가는 길

};