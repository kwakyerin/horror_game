#pragma once

#include <Windows.h>
#include "Image.h"

const int Map_Width = 25;
const int Map_Height = 18;
const int Tile_Size = 32;

//int currentMap;
  
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
    WELL_03, //10
    WELL_04,
    TREE_01,
    TREE_02,
    TREE_03,
    TREE_04, //15
    House_01,//16
    House_02,
    House_03,
    House_04,
    House_05,
    House_06,
    House_07,
    House_08,
    House_09,
    House_10,
    House_11,
    House_12,
    House_13,
    House_14,
    House_15,
    House_16,
    House_17,
    House_18,
    House_19,
    House_20,
    House_21,
    House_22,
    House_23,
    House_24,
    House_25,
    House_26,
    House_27,
    House_28,
    House_29,
    House_30,
    Wood,
    FlOWER,
    ROCK_06,
    House_31,
    House_32,
    House_33,
    House_34,
    House_35,
    House_36,
    House_37,
    House_38,
    House_39,
    House_40,
    House_41,
    House_42,
    House_43,
    House_44,
    House_45,
    Sea_01,
    Sea_02,
    Black,
    Cavewall,
    Krystal_01,
    Krystal_02,
    CaveBottom,
    Cavewall_02,
    Rock_07,
    Krystal_03,
    Skeleton
};

enum MapType {
    Village = 0,
    Govillage,
    Temple,
    Room,
    Cave
};

class Map
{
public:
    Map();

    bool LoadImages();
    void Draw(HDC hdc);
    void changeMap(MapType newMap);

private:
    int map[Map_Height][Map_Width];

    MapType currentMap;

    //마을
    GameImage grassImage;

    GameImage treeTopImage;
    GameImage treeBottomImage;
    GameImage roadImage;
    GameImage dummyImage;
    GameImage minitreeImage;
    GameImage rockImage;
    GameImage woodImage;
    GameImage flowerImage;

    GameImage well_01Image;
    GameImage well_02Image;
    GameImage well_03Image;
    GameImage well_04Image;

    GameImage tree_01Image;
    GameImage tree_02Image;
    GameImage tree_03Image;
    GameImage tree_04Image;

    GameImage house_01Image;
    GameImage house_02Image;
    GameImage house_03Image;
    GameImage house_04Image;
    GameImage house_05Image;
    GameImage house_06Image;
    GameImage house_07Image;
    GameImage house_08Image;
    GameImage house_09Image;
    GameImage house_10Image;
    GameImage house_11Image;
    GameImage house_12Image;
    GameImage house_13Image;
    GameImage house_14Image;
    GameImage house_15Image;
    GameImage house_16Image;
    GameImage house_17Image;
    GameImage house_18Image;
    GameImage house_19Image;
    GameImage house_20Image;
    GameImage house_21Image;
    GameImage house_22Image;
    GameImage house_23Image;
    GameImage house_24Image;
    GameImage house_25Image;
    GameImage house_26Image;
    GameImage house_27Image;
    GameImage house_28Image;
    GameImage house_29Image;
    GameImage house_30Image;
    GameImage house_31Image;
    GameImage house_32Image;
    GameImage house_33Image;
    GameImage house_34Image;
    GameImage house_35Image;
    GameImage house_36Image;
    GameImage house_37Image;
    GameImage house_38Image;
    GameImage house_39Image;
    GameImage house_40Image;
    GameImage house_41Image;
    GameImage house_42Image;
    GameImage house_43Image;
    GameImage house_44Image;
    GameImage house_45Image;

    GameImage rock_06Image;


    //마을 가는 길

    GameImage Sea_01Image;
    GameImage Sea_02Image;

    //동굴

    GameImage BlackImage;
    GameImage CavewallImage;
    GameImage Krystal_01Image;
    GameImage Krystal_02Image;
    GameImage CavebottomImage;
    GameImage Cavewall_02Image;
    GameImage Rock_07Image;
    GameImage Krystal_03Image;
    GameImage SkeletonImage;
};