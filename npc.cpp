#include "NPC.h"
#include "Map.h"

NPC::NPC()
{
    currentNPC = 0;
    dialogueIndex = 0;
    name = L"";
}

bool NPC::IsNPCTile(int tileValue) const
{
    return tileValue == npc_01 ||
        tileValue == npc_02 ||
        tileValue == npc_03 ||
        tileValue == npc_04 ||
        tileValue == npc_05 ||
        tileValue == npc_06;
}

void NPC::StartDialogue(int tileValue)
{
    currentNPC = tileValue;
    dialogueIndex = 0;
    dialogueLines.clear();

    switch (tileValue)
    {
    case npc_01:
        name = L"촌장";

        dialogueLines =
        {
            L"처음 보는 얼굴이구먼.",
            L"요즘 마을에서 이상한 일이 일어나고 있다네.",
            L"밤에는 사찰 근처에 가지 말게."
        };
        break;

    case npc_02:
        name = L"마을 주민";

        dialogueLines =
        {
            L"어젯밤에 이상한 소리를 들었어요.",
            L"산 쪽에서 들린 것 같아요."
        };
        break;

    case npc_03:
        name = L"여행자";

        dialogueLines =
        {
            L"이 마을은 분위기가 이상하군.",
            L"해가 지기 전에 떠나는 게 좋겠어."
        };
        break;

    case npc_04:
        name = L"검객";

        dialogueLines =
        {
            L"숲 안쪽에서 요괴의 기운이 느껴진다.",
            L"혼자 들어가는 건 위험해."
        };
        break;

    case npc_05:
        name = L"스님";

        dialogueLines =
        {
            L"오방색 부적을 모두 모아야 합니다.",
            L"그것만이 봉인을 완성할 방법입니다."
        };
        break;

    case npc_06:
        name = L"소년";

        dialogueLines =
        {
            L"어젯밤에 검은 그림자를 봤어요.",
            L"저쪽 폐가 쪽으로 사라졌어요."
        };
        break;

    default:
        currentNPC = 0;
        name = L"";
        dialogueLines.clear();
        break;
    }
}

bool NPC::NextDialogue()
{
    if (dialogueLines.empty())
    {
        return false;
    }

    dialogueIndex++;

    if (dialogueIndex <
        static_cast<int>(dialogueLines.size()))
    {
        return true;
    }

    ResetDialogue();
    return false;
}

void NPC::ResetDialogue()
{
    currentNPC = 0;
    dialogueIndex = 0;
    name = L"";
    dialogueLines.clear();
}

const std::wstring& NPC::GetName() const
{
    return name;
}

const std::wstring& NPC::GetCurrentDialogue() const
{
    static const std::wstring emptyText = L"";

    if (dialogueLines.empty())
    {
        return emptyText;
    }

    if (dialogueIndex < 0 ||
        dialogueIndex >= static_cast<int>(dialogueLines.size()))
    {
        return emptyText;
    }

    return dialogueLines[dialogueIndex];
}