#include "canvas.h"

void ColorPickerState::Update()
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
        PixelPos pixelPos = ctx()->parent->info()->pixelPos;
        int pos = 3 * (pixelPos.x + pixelPos.y * ctx()->parent->info()->winSize.x);
        ctx()->parent->info()->cur_col[0] = ctx()->parent->get_pixel_buffer()[pos] / 255.0f;
        ctx()->parent->info()->cur_col[1] = ctx()->parent->get_pixel_buffer()[pos + 1] / 255.0f;
        ctx()->parent->info()->cur_col[2] = ctx()->parent->get_pixel_buffer()[pos + 2] / 255.0f;
    }
}

void ColorPickerState::Exit()
{
    ctx()->parent->info()->set_color_picking(false);
}