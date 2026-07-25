#pragma once

#include <string>
#include <vector>

class NPC
{
public:
    NPC();

    bool IsNPCTile(int tileValue) const;

    void StartDialogue(int tileValue);

    bool NextDialogue();

    void ResetDialogue();

    const std::wstring& GetName() const;
    const std::wstring& GetCurrentDialogue() const;

private:
    int currentNPC;
    int dialogueIndex;

    std::wstring name;
    std::vector<std::wstring> dialogueLines;
};
