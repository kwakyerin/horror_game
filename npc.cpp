#include "NPC.h"
#include "Map.h"
#include <Windows.h>

NPC::NPC()
{
    number = 0;

    x = 0;
    y = 0;

    width = 32;
    height = 32;

    name = L"";

    dialogueIndex = 0;
}

void NPC::SetInfo(
    int npcNumber,
    int newX,
    int newY,
    const std::wstring& newName,
    const std::vector<std::wstring>& newDialogue)
{
    number = npcNumber;

    x = newX;
    y = newY;

    name = newName;
    dialogueLines = newDialogue;

    dialogueIndex = 0;
}

bool NPC::IsNear(
    int playerX,
    int playerY,
    int playerWidth,
    int playerHeight) const
{
    const int interactionRange = 32;

    RECT npcRange;

    npcRange.left = x - interactionRange;
    npcRange.top = y - interactionRange;
    npcRange.right = x + width + interactionRange;
    npcRange.bottom = y + height + interactionRange;

    RECT playerRect;

    playerRect.left = playerX;
    playerRect.top = playerY;
    playerRect.right = playerX + playerWidth;
    playerRect.bottom = playerY + playerHeight;

    RECT result;

    return IntersectRect(
        &result,
        &npcRange,
        &playerRect
    );
}

void NPC::ResetDialogue()
{
    dialogueIndex = 0;
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

    dialogueIndex = 0;
    return false;
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

int NPC::GetNumber() const
{
    return number;
}

int NPC::GetX() const
{
    return x;
}

int NPC::GetY() const
{
    return y;
}

void NPC::Talk(int tile, Dialogue& dialogue)
{
    switch (tile)
    {
    case npc_01:
        dialogue.Open(
            L"촌장",
            L"밤에는 절대로 산으로 가지 말게."
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
            L"어젯밤에 검은 그림자가 폐가로 들어가는 걸 봤어요."
        );
        break;
    }
}