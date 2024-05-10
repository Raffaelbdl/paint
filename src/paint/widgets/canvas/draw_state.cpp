#include <iostream>

#include "canvas.h"

void DrawState::Enter()
{
    std::cout << "enter" << "\n";
    ctx()->parent->undo_push_back();
    ctx()->parent->clear_redo();
}

void DrawState::Update()
{
    if (OnClickState::ShouldExit())
    {
        ctx()->ChangeState(ctx()->idle_state);
        return;
    }

    bool focused = ctx()->parent->info()->focused();
    bool within = ctx()->parent->info()->within();
    if (focused && within)
    {
        PixelPos pos = ctx()->parent->info()->pixelPos;
        ImVec2 size = ctx()->parent->info()->winSize;
        ctx()->parent->draw(pos.x, pos.y, size.x, size.y);
    }
}