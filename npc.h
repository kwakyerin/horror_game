#pragma once

#include <string>
#include <vector>

class NPC
{
public:
    NPC();

    void SetInfo(
        int npcNumber,
        int newX,
        int newY,
        const std::wstring& newName,
        const std::vector<std::wstring>& newDialogue
    );

    bool IsNear(
        int playerX,
        int playerY,
        int playerWidth,
        int playerHeight
    ) const;

    void ResetDialogue();
    bool NextDialogue();

    const std::wstring& GetName() const;
    const std::wstring& GetCurrentDialogue() const;

    int GetNumber() const;
    int GetX() const;
    int GetY() const;

private:
    int number;

    int x;
    int y;

    int width;
    int height;

    std::wstring name;
    std::vector<std::wstring> dialogueLines;

    int dialogueIndex;
};