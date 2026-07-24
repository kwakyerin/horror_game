#pragma once

#include <Windows.h>
#include "Image.h"

class Character;

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
    Skeleton,
    Krystal_04,
    Krystal_05,
    Krystal_06,
    Krystal_07,
    Entrance_01,
    Entrance_02,
    Status_01,
    Status_02,
    Rock_09,
    Rock_10,
    Bottom,
    Bed_01,
    Bed_02,
    Closet_01,
    Closet_02,
    Bookshelf_01,
    Bookshelf_02,
    Dishshelf_01,
    Dishshelf_02,
    Roomwall_01,
    Roomwall_02,
    Roomwall_03,
    Clock,
    Ricedummy_01,
    Ricedummy_02,
    Shelf_01,
    Shelf_02,
    Shelf_03,
    Shelf_04,
    Paper,
    Pot,
    Ricedummy,
    Table,
    Chair_01,
    Chair_02,
    Box_01,
    Box_02,
    Barrel_01,
    Barrel_02,
    Barrel_03,
    Barrel_04,
    Treasure_chest_01,
    Treasure_chest_02
};

enum MapType {

    Village = 0,
    Govillage,
    Temple,
    Room,
    Cave,
    Cave_02

};

class Map
{
public:

    Map();

    bool LoadImages();
    void Draw(HDC hdc);
    void changeMap(MapType newMap);
    void Maptransform(Character& character);
    bool IsBlocked(float x, float y);

    MapType GetCurrentMap() const;

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
    GameImage Krystal_04Image;
    GameImage Krystal_05Image;
    GameImage Krystal_06Image;
    GameImage Krystal_07Image;
    GameImage Entrance_01Image;
    GameImage Entrance_02Image;
    GameImage Rock_09Image;
    GameImage Rock_10Image;

    //동굴 아래쪽
    GameImage Status_01Image;
    GameImage Status_02Image;

    //방
    GameImage BottomImage;
    GameImage Bed_01Image;
    GameImage Bed_02Image;
    GameImage Closet_01Image;
    GameImage Closet_02Image;
    GameImage Bookshelf_01Image;
    GameImage Bookshelf_02Image;
    GameImage Dishshelf_01Image;
    GameImage Dishshelf_02Image;
    GameImage Roomwall_01Image;
    GameImage Roomwall_02Image;
    GameImage Roomwall_03Image;
    GameImage ClockImage;
    GameImage Ricedummy_01Image;
    GameImage Ricedummy_02Image;
    GameImage Shelf_01Image;
    GameImage Shelf_02Image;
    GameImage Shelf_03Image;
    GameImage Shelf_04Image;
    GameImage PaperImage;
    GameImage PotImage;
    GameImage RicedummyImage;
    GameImage TableImage;
    GameImage Chair_01Image;
    GameImage Chair_02Image;
    GameImage Box_01Image;
    GameImage Box_02Image;
    GameImage Barrel_01Image;
    GameImage Barrel_02Image;
    GameImage Barrel_03Image;
    GameImage Barrel_04Image;
    GameImage Treasure_chest_01Image;
    GameImage Treasure_chest_02Image;

    /*Box_01,
    Box_02,
    Barrel_01,
    Barrel_02,
    Barrel_03,
    Barrel_04,
    Treasure_chest_01,
    Treasure_chest_02*/

};