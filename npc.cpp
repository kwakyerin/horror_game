#include "NPC.h"
#include "Map.h"

void NPC::Talk(int tile, Dialogue& dialogue)
{
    switch (tile)
    {
    case npc_01:
        dialogue.Open(
            L"촌장",
            {
                L"밤에는 절대로 동굴로 가지 말게.",
                L"산에는 봉인되지 못한 요괴들이 있다네.",
                L"오방색 부적을 모두 찾아야 하네.",
                L"조심하게."
            }
        );
        break;

    case npc_02:
        dialogue.Open(
            L"주민",
            L"어젯밤에 산에서 이상한 소리를 들었어요."
        );
        break;

    case npc_03:
        dialogue.Open(
            L"상인",
            L"필요한 물건이 있으면 말해요."
        );
        break;

    case npc_04:
        dialogue.Open(
            L"여행자",
            L"이 마을에는 뭔가 불길한 기운이 느껴지는군."
        );
        break;

    case npc_05:
        dialogue.Open(
            L"스님",
            L"오방색 부적을 모두 찾아야 봉인을 완성할 수 있습니다."
        );
        break;

    case npc_06:
        dialogue.Open(
            L"아이",
            L"어젯밤에 검은 그림자가 동굴로 들어가는 걸 봤어요."
        );
        break;

    case npc_10:
        dialogue.Open(
            L"의뢰자",
            {
                L"자네가 혹시 퇴마사인가?",
                L"내가 자네를 불렀네.",
                L"이 마을에 요즘 밤마다 요괴들이 나타나서 마을 주민들을 자꾸 괴롭힌다네..",
                L"자네가 부적을 모아서 요괴들을 봉인시켜줄 수 있겠나..?"
                L"공짜로 해줄 순 없겠는가..허허..",
                L"이 마을 곳곳에 숨겨져있는 부적이 총 5개 있을 거라네.",
             L"자네가 직접 찾아서 봉인 장소에 가서 부적을 붙이고 오게나..",
             L"참고로 난 부적 위치랑 봉인 위치 둘 다 모른다네^^",
            L"알아서 찾으시길..그리고 아래쪽 마을에서 두번째 집이 자네가 오늘 밤 묵을 집이라네",
            L"부적 위치는 아마도 주민들이 알고 있을 거라네..사실 난 잘 몰라",
            L"알아서 하시길 그럼 수고"
            }
        );
        break;
    }
}