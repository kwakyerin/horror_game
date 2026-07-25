#include "NPC.h"

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