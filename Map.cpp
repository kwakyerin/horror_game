#include "Map.h"
#include "Image.h"
#include "Character.h"

Map::Map()
{

    currentMap = Village;

    changeMap(Room);

}

bool Map::LoadImages()
{
    bool result = true;

    //바닥
    result &= grassImage.Load(
        L"Image\\Village\\Grass.png"
    );

    //작은 나무(위)
    result &= treeTopImage.Load(
        L"Image\\Village\\Tree_top.png"
    );

    //작은 나무(아래)
    result &= treeBottomImage.Load(
        L"Image\\Village\\Tree_bottom.png"
    );
    
    //길
    result &= roadImage.Load(
        L"Image\\Village\\Road.png"
    );

    result &= dummyImage.Load(
        L"Image\\Village\\Dummy_01.png"
    );

    //수풀
    result &= minitreeImage.Load(
        L"Image\\Village\\Grass_02.png"
    );
    
    //돌
    result &= rockImage.Load(
        L"Image\\Village\\Rock.png"
    );

    //우물
    result &= well_01Image.Load(
        L"Image\\Village\\Well_01.png"
    );
    result &= well_02Image.Load(
        L"Image\\Village\\Well_02.png"
    );
    result &= well_03Image.Load(
        L"Image\\Village\\Well_03.png"
    );
    result &= well_04Image.Load(
        L"Image\\Village\\Well_04.png"
    );

    //큰 나무
    result &= tree_01Image.Load(
        L"Image\\Village\\Tree_01.png"
    );
    result &= tree_02Image.Load(
        L"Image\\Village\\Tree_02.png"
    );
    result &= tree_03Image.Load(
        L"Image\\Village\\Tree_03.png"
    );
    result &= tree_04Image.Load(
        L"Image\\Village\\Tree_04.png"
    );

    //집
    result &= house_01Image.Load(
        L"Image\\Village\\House_01.png"
    );
    result &= house_02Image.Load(
        L"Image\\Village\\House_02.png"
    );
    result &= house_03Image.Load(
        L"Image\\Village\\House_03.png"
    );
    result &= house_04Image.Load(
        L"Image\\Village\\House_04.png"
    );
    result &= house_05Image.Load(
        L"Image\\Village\\House_05.png"
    );
    result &= house_06Image.Load(
        L"Image\\Village\\House_06.png"
    );
    result &= house_07Image.Load(
        L"Image\\Village\\House_07.png"
    );
    result &= house_08Image.Load(
        L"Image\\Village\\House_08.png"
    );
    result &= house_09Image.Load(
        L"Image\\Village\\House_09.png"
    );
    result &= house_10Image.Load(
        L"Image\\Village\\House_10.png"
    );
    result &= house_11Image.Load(
        L"Image\\Village\\House_11.png"
    );
    result &= house_12Image.Load(
        L"Image\\Village\\House_12.png"
    );
    result &= house_13Image.Load(
        L"Image\\Village\\House_13.png"
    );
    result &= house_14Image.Load(
        L"Image\\Village\\House_14.png"
    );
    result &= house_15Image.Load(
        L"Image\\Village\\House_15.png"
    );
    result &= house_16Image.Load(
        L"Image\\Village\\House_16.png"
    );
    result &= house_17Image.Load(
        L"Image\\Village\\House_17.png"
    );
    result &= house_18Image.Load(
        L"Image\\Village\\House_18.png"
    );
    result &= house_19Image.Load(
        L"Image\\Village\\House_19.png"
    );
    result &= house_20Image.Load(
        L"Image\\Village\\House_20.png"
    );
    result &= house_21Image.Load(
        L"Image\\Village\\House_21.png"
    );
    result &= house_22Image.Load(
        L"Image\\Village\\House_22.png"
    );
    result &= house_23Image.Load(
        L"Image\\Village\\House_23.png"
    );
    result &= house_24Image.Load(
        L"Image\\Village\\House_24.png"
    );
    result &= house_25Image.Load(
        L"Image\\Village\\House_25.png"
    );
    result &= house_26Image.Load(
        L"Image\\Village\\House_26.png"
    );
    result &= house_27Image.Load(
        L"Image\\Village\\House_27.png"
    );
    result &= house_28Image.Load(
        L"Image\\Village\\House_28.png"
    );
    result &= house_29Image.Load(
        L"Image\\Village\\House_29.png"
    );
    result &= house_30Image.Load(
        L"Image\\Village\\House_30.png"
    );
    result &= house_31Image.Load(
        L"Image\\Village\\House_31.png"
    );
    result &= house_32Image.Load(
        L"Image\\Village\\House_32.png"
    );
    result &= house_33Image.Load(
        L"Image\\Village\\House_33.png"
    );
    result &= house_34Image.Load(
        L"Image\\Village\\House_34.png"
    );
    result &= house_35Image.Load(
        L"Image\\Village\\House_35.png"
    );
    result &= house_36Image.Load(
        L"C:\\Horror_Game\\Horror_Game\\Image\\Village\\House_36.png"
    );
    result &= house_37Image.Load(
        L"Image\\Village\\House_37.png"
    );
    result &= house_38Image.Load(
        L"Image\\Village\\House_38.png"
    );
    result &= house_39Image.Load(
        L"Image\\Village\\House_39.png"
    );
    result &= house_40Image.Load(
        L"Image\\Village\\House_40.png"
    );
    result &= house_41Image.Load(
        L"Image\\Village\\House_41.png"
    );
    result &= house_42Image.Load(
        L"Image\\Village\\House_42.png"
    );
    result &= house_43Image.Load(
        L"Image\\Village\\House_43.png"
    );
    result &= house_44Image.Load(
        L"Image\\Village\\House_44.png"
    );
    result &= house_45Image.Load(
        L"Image\\Village\\House_45.png"
    );

    //울타리
    result &= woodImage.Load(
        L"Image\\Village\\Wood.png"
    );

    //꽃
    result &= flowerImage.Load(
        L"Image\\Village\\Grass_03.png"
    );

    //돌(2 버전)
    result &= rock_06Image.Load(
        L"Image\\Village\\Rock_06.png"
    );

    //바다(1,2)
    result &= Sea_01Image.Load(
        L"Image\\Village\\Sea_01.png"
    );
    result &= Sea_02Image.Load(
        L"Image\\Village\\Sea_02.png"
    );

    //동굴 배경
    result &= BlackImage.Load(
        L"Image\\Cave\\Black.png"
    );

    //동굴 벽
    result &= CavewallImage.Load(
        L"Image\\Cave\\Cavewall.png"
    );

    //크리스탈
    result &= Krystal_01Image.Load(
        L"Image\\Cave\\Krystal_01.png"
    );
    result &= Krystal_02Image.Load(
        L"Image\\Cave\\Krystal_02.png"
    );

    //동굴 바닥
    result &= CavebottomImage.Load(
        L"Image\\Cave\\Cavebottom.png"
    );

    result &= Cavewall_02Image.Load(
        L"Image\\Cave\\Cavewall_02.png"
    );

    //돌
    result &= Rock_07Image.Load(
        L"Image\\Cave\\Rock_07.png"
    );

    //작은 크리스탈
    result &= Krystal_03Image.Load(
        L"Image\\Cave\\Krystal_03.png"
    );

    //해골
    result &= SkeletonImage.Load(
        L"Image\\Cave\\Skeleton.png"
    );

    //큰 크리스탈

    result &= Krystal_04Image.Load(
        L"Image\\Cave\\Krystal_04.png"
    );
    result &= Krystal_05Image.Load(
        L"Image\\Cave\\Krystal_05.png"
    );
    result &= Krystal_06Image.Load(
        L"Image\\Cave\\Krystal_06.png"
    );
    result &= Krystal_07Image.Load(
        L"Image\\Cave\\Krystal_07.png"
    );

    result &= Entrance_01Image.Load(
        L"Image\\Village\\Rock_09.png"
    );
    result &= Entrance_01Image.Load(
        L"C:\\Horror_Game\\Horror_Game\\Image\\Village\\Rock_10.png"
    );

    //동굴 입구
    result &= Entrance_01Image.Load(
        L"Image\\Cave\\Entrance_01.png"
    );
    result &= Entrance_02Image.Load(
        L"Image\\Cave\\Entrance_02.png"
    );

    //동굴 조각상
    result &= Status_01Image.Load(
        L"Image\\Cave\\Status_01.png"
    );
    result &= Status_02Image.Load(
        L"Image\\Cave\\Status_02.png"
    );

    //방바닥
    result &= BottomImage.Load(
        L"Image\\Room\\Bottom.png"
    );

    //침대
    result &= Bed_01Image.Load(
        L"Image\\Room\\Bed_01.png"
    );
    result &= Bed_02Image.Load(
        L"Image\\Room\\Bed_02.png"
    );

    //옷장
    result &= Closet_01Image.Load(
        L"Image\\Room\\Closet_01.png"
    );
    result &= Closet_02Image.Load(
        L"Image\\Room\\Closet_02.png"
    );

    //책장
    result &= Bookshelf_01Image.Load(
        L"Image\\Room\\Bookshelf_01.png"
    );
    result &= Bookshelf_02Image.Load(
        L"Image\\Room\\Bookshelf_02.png"
    );

    //그릇선반
    result &= Dishshelf_01Image.Load(
        L"Image\\Room\\Dishshelf_01.png"
    );
    result &= Dishshelf_02Image.Load(
        L"Image\\Room\\Dishshelf_02.png"
    );

    //벽
    result &= Roomwall_01Image.Load(
        L"Image\\Room\\Roomwall_01.png"
    );
    result &= Roomwall_02Image.Load(
        L"Image\\Room\\Roomwall_02.png"
    );
    result &= Roomwall_03Image.Load(
        L"Image\\Room\\Roomwall_03.png"
    );

    //시계
    result &= ClockImage.Load(
        L"Image\\Room\\Clock.png"
    );

    //쌀더미
    result &= Ricedummy_01Image.Load(
        L"Image\\Room\\Ricedummy_01.png"
    );
    result &= Ricedummy_02Image.Load(
        L"Image\\Room\\Ricedummy_02.png"
    );

    //선반
    result &= Shelf_01Image.Load(
        L"Image\\Room\\Shelf_01.png"
    );
    result &= Shelf_02Image.Load(
        L"Image\\Room\\Shelf_02.png"
    );
    result &= Shelf_03Image.Load(
        L"Image\\Room\\Shelf_03.png"
    );
    result &= Shelf_04Image.Load(
        L"Image\\Room\\Shelf_04.png"
    );

    //종이
    result &= PaperImage.Load(
        L"Image\\Room\\Paper.png"
    );

    //항아리
    result &= PotImage.Load(
        L"Image\\Room\\Pot.png"
    );

    result &= RicedummyImage.Load(
        L"Image\\Village\\Rice_dummy.png"
    );

    result &= TableImage.Load(
        L"Image\\Room\\Table.png"
    );
    result &= Chair_01Image.Load(
        L"Image\\Room\\Chair_01.png"
    );
    result &= Chair_02Image.Load(
        L"Image\\Room\\Chair_02.png"
    );

    result &= Box_01Image.Load(
        L"Image\\Room\\Box_01.png"
    );
    result &= Box_02Image.Load(
        L"Image\\Room\\Box_02.png"
    );

    result &= Barrel_01Image.Load(
        L"Image\\Room\\Barrel_01.png"
    );
    result &= Barrel_02Image.Load(
        L"Image\\Room\\Barrel_02.png"
    );
    result &= Barrel_03Image.Load(
        L"Image\\Room\\Barrel_03.png"
    );
    result &= Barrel_04Image.Load(
        L"Image\\Room\\Barrel_04.png"
    );

    result &= Treasure_chest_01Image.Load(
        L"Image\\Room\\Treasure_chest_01.png"
    );
    result &= Treasure_chest_02Image.Load(
        L"Image\\Room\\Treasure_chest_02.png"
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

            case House_31:
                grassImage.Draw(hdc, drawX, drawY);
                house_31Image.Draw(hdc, drawX, drawY);
                break;

            case House_32:
                grassImage.Draw(hdc, drawX, drawY);
                house_32Image.Draw(hdc, drawX, drawY);
                break;
            case House_33:
                grassImage.Draw(hdc, drawX, drawY);
                house_30Image.Draw(hdc, drawX, drawY);
                break;
            case House_34:
                grassImage.Draw(hdc, drawX, drawY);
                house_34Image.Draw(hdc, drawX, drawY);
                break;
            case House_35:
                grassImage.Draw(hdc, drawX, drawY);
                house_35Image.Draw(hdc, drawX, drawY);
                break;
            case House_36:
                grassImage.Draw(hdc, drawX, drawY);
                house_36Image.Draw(hdc, drawX, drawY);
                break;
            case House_37:
                grassImage.Draw(hdc, drawX, drawY);
                house_37Image.Draw(hdc, drawX, drawY);
                break;
            case House_38:
                grassImage.Draw(hdc, drawX, drawY);
                house_38Image.Draw(hdc, drawX, drawY);
                break;
            case House_39:
                grassImage.Draw(hdc, drawX, drawY);
                house_39Image.Draw(hdc, drawX, drawY);
                break;
            case House_40:
                grassImage.Draw(hdc, drawX, drawY);
                house_40Image.Draw(hdc, drawX, drawY);
                break;
            case House_41:
                grassImage.Draw(hdc, drawX, drawY);
                house_41Image.Draw(hdc, drawX, drawY);
                break;
            case House_42:
                grassImage.Draw(hdc, drawX, drawY);
                house_42Image.Draw(hdc, drawX, drawY);
                break;
            case House_43:
                grassImage.Draw(hdc, drawX, drawY);
                house_43Image.Draw(hdc, drawX, drawY);
                break;
            case House_44:
                grassImage.Draw(hdc, drawX, drawY);
                house_44Image.Draw(hdc, drawX, drawY);
                break;
            case House_45:
                grassImage.Draw(hdc, drawX, drawY);
                house_45Image.Draw(hdc, drawX, drawY);
                break;

            //마을 가는 길 
            case Sea_01:
                Sea_01Image.Draw(hdc, drawX, drawY);
                break;

            case Sea_02:
                Sea_02Image.Draw(hdc, drawX, drawY);
                break;

            //동굴
            case Black:
                BlackImage.Draw(hdc, drawX, drawY);
                break;

            case Cavewall:
                CavewallImage.Draw(hdc, drawX, drawY);
                break;

            case Krystal_01:
                CavebottomImage.Draw(hdc, drawX, drawY);
                Krystal_01Image.Draw(hdc, drawX, drawY);
                break;

            case Krystal_02:
                CavebottomImage.Draw(hdc, drawX, drawY);
                Krystal_02Image.Draw(hdc, drawX, drawY);
                break;

            case CaveBottom:
                CavebottomImage.Draw(hdc, drawX, drawY);
                break;

            case Cavewall_02:
                Cavewall_02Image.Draw(hdc, drawX, drawY);
                break;

            case Rock_07:
                CavebottomImage.Draw(hdc, drawX, drawY);
                Rock_07Image.Draw(hdc, drawX, drawY);
                break;

            case Krystal_03:
                CavebottomImage.Draw(hdc, drawX, drawY);
                Krystal_03Image.Draw(hdc, drawX, drawY);
                break;

            case Skeleton:
                CavebottomImage.Draw(hdc, drawX, drawY);
                SkeletonImage.Draw(hdc, drawX, drawY);
                break;

            case Krystal_04:
                CavebottomImage.Draw(hdc, drawX, drawY);
                Krystal_04Image.Draw(hdc, drawX, drawY);
                break;

            case Krystal_05:
                CavebottomImage.Draw(hdc, drawX, drawY);
                Krystal_05Image.Draw(hdc, drawX, drawY);
                break;

            case Krystal_06:
                CavebottomImage.Draw(hdc, drawX, drawY);
                Krystal_06Image.Draw(hdc, drawX, drawY);
                break;

            case Krystal_07:
                CavebottomImage.Draw(hdc, drawX, drawY);
                Krystal_07Image.Draw(hdc, drawX, drawY);
                break;

            case Entrance_01:
               // CavebottomImage.Draw(hdc, drawX, drawY);
                Entrance_01Image.Draw(hdc, drawX, drawY);
                break;

            case Entrance_02:
                // CavebottomImage.Draw(hdc, drawX, drawY);
                Entrance_02Image.Draw(hdc, drawX, drawY);
                break;

            case Status_01:
                //CavebottomImage.Draw(hdc, drawX, drawY);
                Status_01Image.Draw(hdc, drawX, drawY);
                break;

            case Status_02:
                Status_02Image.Draw(hdc, drawX, drawY);
                break;

            case Bottom:
                BottomImage.Draw(hdc, drawX, drawY);
                break;

            case Bed_01:
                BottomImage.Draw(hdc, drawX, drawY);
                Bed_01Image.Draw(hdc, drawX, drawY);
                break;

            case Bed_02:
                BottomImage.Draw(hdc, drawX, drawY);
                Bed_02Image.Draw(hdc, drawX, drawY);
                break;

            case Closet_01:
                Closet_01Image.Draw(hdc, drawX, drawY);
                break;

            case Closet_02:
                Closet_02Image.Draw(hdc, drawX, drawY);
                break;

            case Bookshelf_01:
                Bookshelf_01Image.Draw(hdc, drawX, drawY);
                break;
            case Bookshelf_02:
                Bookshelf_02Image.Draw(hdc, drawX, drawY);
                break;

            case Dishshelf_01:
                Dishshelf_01Image.Draw(hdc, drawX, drawY);
                break;

            case Dishshelf_02:
                Dishshelf_02Image.Draw(hdc, drawX, drawY);
                break;

            case Roomwall_01:
                Roomwall_01Image.Draw(hdc, drawX, drawY);
                break;

            case Roomwall_02:
                Roomwall_02Image.Draw(hdc, drawX, drawY);
                break;

            case Roomwall_03:
                Roomwall_03Image.Draw(hdc, drawX, drawY);
                break;

            case Clock:
                Roomwall_02Image.Draw(hdc, drawX, drawY);
                ClockImage.Draw(hdc, drawX, drawY);
                break;

            case Ricedummy_01:
                BottomImage.Draw(hdc, drawX, drawY);
                Ricedummy_01Image.Draw(hdc, drawX, drawY);
                break;

            case Ricedummy_02:
                BottomImage.Draw(hdc, drawX, drawY);
                Ricedummy_02Image.Draw(hdc, drawX, drawY);
                break;

            case Shelf_01:
                Shelf_01Image.Draw(hdc, drawX, drawY);
                break;

            case Shelf_02:
                Shelf_02Image.Draw(hdc, drawX, drawY);
                break;
                
            case Shelf_03:
                Shelf_03Image.Draw(hdc, drawX, drawY);
                break;

            case Shelf_04:
                Shelf_04Image.Draw(hdc, drawX, drawY);
                break;

            case Paper:
                BottomImage.Draw(hdc, drawX, drawY);
                PaperImage.Draw(hdc, drawX, drawY);
                break;

            case Pot:
                BottomImage.Draw(hdc, drawX, drawY);
                PotImage.Draw(hdc, drawX, drawY);
                break;

            case Ricedummy:
                BottomImage.Draw(hdc, drawX, drawY);
                RicedummyImage.Draw(hdc, drawX, drawY);
                break;

            case Table:
                BottomImage.Draw(hdc, drawX, drawY);
                TableImage.Draw(hdc, drawX, drawY);
                break;

            case Chair_01:
                BottomImage.Draw(hdc, drawX, drawY);
                Chair_01Image.Draw(hdc, drawX, drawY);
                break;

            case Chair_02:
                BottomImage.Draw(hdc, drawX, drawY);
                Chair_02Image.Draw(hdc, drawX, drawY);
                break;
            
            case Box_01:
                BottomImage.Draw(hdc, drawX, drawY);
                Box_01Image.Draw(hdc, drawX, drawY);
                break;

            case Box_02:
                BottomImage.Draw(hdc, drawX, drawY);
                Box_02Image.Draw(hdc, drawX, drawY);
                break;

            case Barrel_01:
                Roomwall_03Image.Draw(hdc, drawX, drawY);
                Barrel_01Image.Draw(hdc, drawX, drawY);
                break;

            case Barrel_02:
                Roomwall_03Image.Draw(hdc, drawX, drawY);
                Barrel_02Image.Draw(hdc, drawX, drawY);
                break;

            case Barrel_03:
                BottomImage.Draw(hdc, drawX, drawY);
                Barrel_03Image.Draw(hdc, drawX, drawY);
                break;

            case Barrel_04:
                BottomImage.Draw(hdc, drawX, drawY);
                Barrel_04Image.Draw(hdc, drawX, drawY);
                break;

            case Treasure_chest_01:
                BottomImage.Draw(hdc, drawX, drawY);
                Treasure_chest_01Image.Draw(hdc, drawX, drawY);
                break;

            case Treasure_chest_02:
                BottomImage.Draw(hdc, drawX, drawY);
                Treasure_chest_02Image.Draw(hdc, drawX, drawY);
                break;
            }
        }
    }
}

void Map::changeMap(MapType newMap)
{
    currentMap = newMap;

    switch (currentMap)
    {
    case Village:

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

        map[2][10] = TILE_ROAD;
        map[2][9] = TILE_ROAD;
        map[2][8] = TILE_ROAD;
        map[2][7] = TILE_ROAD;
        map[2][11] = TILE_ROAD;
        map[2][12] = TILE_ROAD;

        map[10][20] = 3;
        map[11][20] = 3;

        //더미
        map[9][13] = 4;
        map[9][12] = 4;

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

        map[2][16] = TREE_01;
        map[3][16] = TREE_03;
        map[2][17] = TREE_02;
        map[3][17] = TREE_04;

        //집1(주인공 집)
        map[9][14] = 22;
        map[9][15] = 23;
        map[9][16] = 18;
        map[9][17] = 19;
        map[9][18] = 20;
        map[9][19] = 21;
        map[9][20] = 16; //문
        map[9][21] = 17;
        map[8][20] = 24; //문
        map[7][20] = House_18; //문

        //건들 X
        /*
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
        map[6][15] = 43;
        map[6][16] = 44;
        map[6][17] = 50;
        map[6][18] = 60;*/

        //집2
        map[1][12] = 16;
        map[0][12] = 24;

        //나무 울타리

        for (int i = 19; i >= 13; i--) {
            map[11][i] = Wood;
        }
        map[11][21] = Wood;
        map[11][22] = Wood;
        map[11][23] = Wood;

        //꽃 풀숲
        map[11][9] = FlOWER;
        map[11][10] = FlOWER;
        map[14][20] = FlOWER;
        map[14][21] = FlOWER;

        //돌_06
        map[4][8] = ROCK_06;
        map[5][7] = ROCK_06;

        break;

    case Govillage:

        //길
        for (int i = 5; i < 25; i++) {
            map[4][i] = TILE_ROAD;
            map[5][i] = TILE_ROAD;
        }

        map[5][4] = TILE_ROAD;
        map[6][4] = TILE_ROAD;

        for (int i = 0; i < 4; i++) {
            map[6][i] = TILE_ROAD;
            map[7][i] = TILE_ROAD;
        }

        //바다
        for (int i = 0; i < 25; i++) {
            map[11][i] = Sea_01;
        }

        for (int i = 0; i < 25; i++) {
            map[0][i] = Sea_02;
        }

        for (int i = 0; i < 25; i++) {

            for (int j = 12; j < 18; j++) {
                map[j][i] = Sea_02;
            }
        }

        //큰 나무
        map[6][6] = TREE_01;
        map[7][6] = TREE_03;
        map[6][7] = TREE_02;
        map[7][7] = TREE_04;

        map[8][2] = TREE_01;
        map[9][2] = TREE_03;
        map[8][3] = TREE_02;
        map[9][3] = TREE_04;

        map[2][8] = TREE_01;
        map[3][8] = TREE_03;
        map[2][9] = TREE_02;
        map[3][9] = TREE_04;

        map[7][15] = TREE_01;
        map[8][15] = TREE_03;
        map[7][16] = TREE_02;
        map[8][16] = TREE_04;

        //작은 나무
        map[2][2] = 1;
        map[3][2] = 2;

        map[2][3] = 1;
        map[3][3] = 2;

        map[8][20] = 1;
        map[9][20] = 2;

        map[1][5] = 1;
        map[2][5] = 2;

        map[7][21] = 1;
        map[8][21] = 2;

        map[2][14] = 1;
        map[3][14] = 2;

        //작은 풀숲
        map[5][0] = TILE_MINITREE;
        map[4][2] = TILE_MINITREE;

        map[2][18] = TILE_MINITREE;

        map[7][11] = TILE_MINITREE;
        map[8][12] = TILE_MINITREE;
        map[8][13] = TILE_MINITREE;

        //돌
        map[8][0] = TILE_ROCK;
        map[1][11] = TILE_ROCK;
        map[10][5] = TILE_ROCK;
        map[7][19] = TILE_ROCK;

        //꽃
        map[2][19] = FlOWER;
        map[9][8] = FlOWER;
        map[10][9] = FlOWER;

        break;

    case Temple:

        // 절 맵 배치

        /*map[8][8] = Rock_09;
        map[9][8] = Rock_10;*/

        break;

    case Room:

        //배경
        for (int y = 0; y < Map_Height; y++)
        {
            for (int x = 0; x < Map_Width; x++)
            {
                map[y][x] = Black;
            }
        }

        //방바닥
        for (int i = 5; i < 16; i++) {
            for (int j = 5; j < 18; j++) {
                map[i][j] = Bottom;
            }
        }

        map[16][16] = Bottom;
        map[17][16] = Bottom;

        //벽
        for (int i = 5; i < 18; i++) {
            map[2][i] = Roomwall_01;
        }

        for (int i = 5; i < 18; i++) {
            map[3][i] = Roomwall_02;
        }

        for (int i = 2; i < 17; i++) {
            map[i][4] = Roomwall_01;
        }

        for (int i = 2; i < 17; i++) {
            map[i][18] = Roomwall_01;
        }

        for (int i = 5; i < 16; i++) {
            map[16][i] = Roomwall_01;
        }

        map[16][17] = Roomwall_01;

 
        for (int i = 8; i < 18; i++) {
            map[4][i] = Roomwall_03;
        }

        //침대
        map[7][17] = Bed_01;
        map[8][17] = Bed_02;

        //옷장
        map[4][6] = Closet_01;
        map[5][6] = Closet_02;

        //책장
        map[4][5] = Bookshelf_01;
        map[5][5] = Bookshelf_02;

        //그릇선반
        map[4][7] = Dishshelf_01;
        map[5][7] = Dishshelf_02;

        //시계
        map[3][15] = Clock;

        //쌀더미
       /* map[13][5] = Ricedummy_01;
        map[14][5] = Ricedummy_02;

        map[14][5] = Ricedummy_01;
        map[15][5] = Ricedummy_02;

        map[13][6] = Ricedummy_01;
        map[14][6] = Ricedummy_02;*/

        //선반
        map[4][8] = Shelf_01;
        map[5][8] = Shelf_02;
        map[4][9] = Shelf_03;
        map[5][9] = Shelf_04;

        map[4][11] = Shelf_03;
        map[5][11] = Shelf_04;

        //종이
        map[7][10] = Paper;
        map[5][17] = Paper;
        map[12][13] = Paper;

        //항아리
        map[14][6] = Pot;
        map[14][7] = Pot;

        //소형 쌀더미
        map[15][5] = Ricedummy;
        map[15][6] = Ricedummy;

        //의자&책상
        map[8][13] = Table;
        map[8][12] = Chair_01;
        map[8][14] = Chair_02;

        //상자
        /*map[10][10] = Box_01;
        map[11][10] = Box_02;*/

        //와인통
        map[4][13] = Barrel_01;
        map[4][14] = Barrel_02;
        map[5][13] = Barrel_03;
        map[5][14] = Barrel_04;
        
        //보물상자
        map[8][5] = Treasure_chest_01;
        map[9][5] = Treasure_chest_02;

        break;

    case Cave:

        //배경

        for (int y = 0; y < Map_Height; y++)
        {
            for (int x = 0; x < Map_Width; x++)
            {
                map[y][x] = Black;
            }
        }

        //벽

        for (int i = 4; i < 20; i++) {
            map[2][i] = Cavewall;
        }

        for (int i = 4; i < 20; i++) {
            map[3][i] = Cavewall_02;
        }

        //크리스탈
        map[3][4] = Krystal_02;
        map[4][4] = Krystal_01;

        map[12][15] = Krystal_02;
        map[13][15] = Krystal_01;

        map[14][18] = Krystal_02;
        map[15][18] = Krystal_01;

        //작은 크리스탈
        map[9][9] = Krystal_03;

        //큰 크리스탈
        map[7][15] = Krystal_04;
        map[7][16] = Krystal_05;
        map[6][15] = Krystal_06;
        map[6][16] = Krystal_07;

        //바닥
        map[8][0] = CaveBottom;
        map[8][1] = CaveBottom;
        map[8][2] = CaveBottom;
        map[8][3] = CaveBottom;
        map[9][0] = CaveBottom;
        map[9][1] = CaveBottom;
        map[9][2] = CaveBottom;
        map[9][3] = CaveBottom;

        for (int i = 4; i < 20; i++) {
            map[10][i] = CaveBottom;
            map[11][i] = CaveBottom;
        }
        //바닥 첫줄
        for (int i = 6; i < 20; i++) {
            map[4][i] = CaveBottom;
        }

        for (int i = 4; i < 15; i++) {
            map[6][i] = CaveBottom;
            map[7][i] = CaveBottom;
        }

        for (int i = 17; i < 20; i++) {
            map[6][i] = CaveBottom;
            map[7][i] = CaveBottom;
        }

        for (int i = 4; i < 20; i++) {
            map[5][i] = CaveBottom;
            map[8][i] = CaveBottom;
        }

        for (int i = 4; i < 9; i++) {
            map[9][i] = CaveBottom;
        }

        for (int i = 10; i < 20; i++) {
            map[9][i] = CaveBottom;
        }


        for (int i = 4; i < 15; i++) {
            map[12][i] = CaveBottom;
            map[13][i] = CaveBottom;
        }

        for (int i = 16; i < 20; i++) {
            map[12][i] = CaveBottom;
            map[13][i] = CaveBottom;
        }

        for (int i = 4; i < 18; i++) {
            map[14][i] = CaveBottom;
        }

        map[14][19] = CaveBottom;

        for (int i = 4; i < 18; i++) {
            map[15][i] = CaveBottom;
        }

        map[15][19] = CaveBottom;

        //돌
        map[15][15] = Rock_09;
        map[15][16] = Rock_10;

        //아래로 내려가는 길
        map[16][11] = CaveBottom;
        map[17][11] = CaveBottom;
        map[16][12] = CaveBottom;
        map[17][12] = CaveBottom;
        map[16][13] = CaveBottom;
        map[17][13] = CaveBottom;

        //돌
        map[14][14] = Rock_07;
        map[4][5] = Rock_07;
        map[6][10] = Rock_07;
        map[12][13] = Rock_07;
        map[14][6] = Rock_07;
        map[5][18] = Rock_07;

        //해골

        map[8][19] = Skeleton;
        map[11][5] = Skeleton;

        break;

    case Cave_02:

        //검은 배경
        for (int y = 0; y < Map_Height; y++)
        {
            for (int x = 0; x < Map_Width; x++)
            {
                map[y][x] = Black;
            }
        }

        //동굴벽
        for (int i = 4; i < 20; i++) {
            map[2][i] = Cavewall;
        }

        for (int i = 4; i < 20; i++) {
            map[3][i] = Cavewall_02;
        }

        //동굴 바닥
        for (int i = 4; i < 17; i++) {
            for (int j = 4; j < 20; j++) {
                map[i][j] = CaveBottom;
            }
        }

        for (int i = 0; i < 4; i++) {
            for (int j = 11; j < 14; j++) {
                map[i][j] = CaveBottom;
            }
        }

        //조각상

        map[15][8] = Status_01;
        map[14][8] = Status_02;

        break;
    }

}

//맵 충돌체크
bool Map::IsBlocked(float x, float y)
{
    int tileX = static_cast<int>(x) / Tile_Size;
    int tileY = static_cast<int>(y) / Tile_Size;

    if (tileX < 0 || tileX >= Map_Width || tileY < 0 || tileY >= Map_Height)
    {
        return true;
    }

    int tile = map[tileY][tileX];

    switch (tile)
    {
    case TILE_TREE_TOP:
    case TILE_TREE_BOTTOM:
    case TILE_MINITREE:
    case FlOWER:
    case Wood:

    case TREE_01:
    case TREE_02:
    case TREE_03:
    case TREE_04:

    case WELL_01:
    case WELL_02:
    case WELL_03:
    case WELL_04:

    case ROCK_06:

    case Sea_01:
    case Sea_02:

    /*case House_01:
    case House_02:
    case House_03:
    case House_04:*/

    case Rock_07:
    case Krystal_01:
    case Krystal_02:
    case Krystal_03:
    case Skeleton:
    case Krystal_04:
    case Krystal_05:
    case Krystal_06:
    case Krystal_07:
    case Cavewall:
    case Cavewall_02:
    case Black:
    case Bed_01:
    case Bed_02:
    case Paper:

    case Roomwall_01:
    case Roomwall_02:
    case Roomwall_03:

    case Table:
    case Chair_01:
    case Chair_02:

    case Shelf_01:
    case Shelf_02:
    case Shelf_03:
    case Shelf_04:

    case Ricedummy:
    case Pot:

    case Barrel_01:
    case Barrel_02:
    case Barrel_03:
    case Barrel_04:

    case Treasure_chest_01:
    case Treasure_chest_02:

        return true;
    }

    return false;
}

//맵 순간이동(수정중)
void Map::Maptransform(Character& character) {

    int tileX = static_cast<int>(character.GetX()) / Tile_Size;
    int tileY = static_cast<int>(character.GetY()) / Tile_Size;

    //마을->마을 가는길
    if (currentMap == MapType::Village && tileX == 0 && (tileY == 3 || tileY == 4))
    {
        changeMap(MapType::Govillage);
        character.SetPosition(700.0f, 128.0f);
    }

    //마을 가는길->마을
    if (currentMap == MapType::Govillage && tileX == 23 && (tileY == 3 || tileY == 4))
    {
        changeMap(MapType::Village);
        character.SetPosition(700.0f, 128.0f);

        //마을로 넘어갈 때 스폰지역
        if (tileY == 3)
            character.SetPosition(1 * Tile_Size, 4 * Tile_Size);
        else
            character.SetPosition(1 * Tile_Size, 5 * Tile_Size);
    }

    //마을->동굴
    if (currentMap == MapType::Village && tileY == 0 && (tileX == 5 || tileX == 6))
    {
        changeMap(MapType::Cave);

        character.SetPosition(1 * Tile_Size, 9 * Tile_Size);

    }

    //동굴->마을
    if (currentMap == MapType::Cave &&tileX == 0 &&tileY == 8)
    {
        changeMap(MapType::Village);

        character.SetPosition(5 * Tile_Size, 2 * Tile_Size);
    }

    //동굴->동굴 안

    //마을->주인공 집

    if (currentMap == MapType::Village && tileX == 20 && tileY == 8)
    {
        changeMap(MapType::Room);

        character.SetPosition(16 * Tile_Size, 16 * Tile_Size);
    }

    //주인공 집->마을
    if (currentMap == MapType::Room && tileX == 16 && tileY == 17)
    {
        changeMap(MapType::Village);

        character.SetPosition(20 * Tile_Size, 9 * Tile_Size);
    }

    //마을->숲

    //사찰->동굴
    
}

MapType Map::GetCurrentMap() const
{
    return currentMap;
}
