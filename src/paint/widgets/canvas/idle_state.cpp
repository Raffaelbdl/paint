#include "canvas.h"

void IdleState::Update()
{
    if (ImGui::IsMouseDown(ImGuiMouseButton(0)))
    {
        // if (ctx()->parent->is_color_picking)
        // {
        //     ctx()->ChangeState(ctx()->colorPicker_state);
        //     return;
        // }
        ctx()->ChangeState(ctx()->draw_state);
        return;
    }
}