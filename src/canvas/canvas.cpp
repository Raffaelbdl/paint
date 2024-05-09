#include <imgui.h>
#include "canvas/canvas.h"
#include "canvas.h"

bool OnClickState::ShouldExit()
{
    // Exit if mouse up
    return !ImGui::IsMouseDown(ImGuiMouseButton(0));
}

void ColorPickerState::Enter()
{
}

void ColorPickerState::Update()
{
    if (OnClickState::ShouldExit())
    {
        ctx()->ChangeState(ctx()->idle_state);
        return;
    }

    if (ctx()->scene->is_focused && ctx()->scene->within)
    {
        int pos = (ctx()->scene->pixel.x + ctx()->scene->pixel.y * ctx()->scene->winSize.x) * 3;

        float col[3];
        col[0] = (float)ctx()->scene->get_pixel_buffer()[pos] / 255.0f;
        col[1] = (float)ctx()->scene->get_pixel_buffer()[pos + 1] / 255.0f;
        col[2] = (float)ctx()->scene->get_pixel_buffer()[pos + 2] / 255.0f;

        ctx()->scene->set_cur_col(col);
    }
}

void ColorPickerState::Exit()
{
    ctx()->scene->is_color_picking = false;
}

void DrawState::Enter()
{
}

void DrawState::Update()
{
    if (OnClickState::ShouldExit())
    {
        ctx()->ChangeState(ctx()->idle_state);
        return;
    }

    if (ctx()->scene->is_focused && ctx()->scene->within)
    {
        ctx()->scene->draw(ctx()->scene->pixel.x, ctx()->scene->pixel.y, ctx()->scene->winSize.x, ctx()->scene->winSize.y);
    }
}

void DrawState::Exit()
{
}

void IdleState::Enter()
{
}
void IdleState::Update()
{
    if (ImGui::IsMouseDown(ImGuiMouseButton(0)))
    {
        if (ctx()->scene->is_color_picking)
        {
            ctx()->ChangeState(ctx()->colorPicker_state);
            return;
        }
        ctx()->ChangeState(ctx()->draw_state);
        return;
    }
}

void IdleState::Exit()
{
}
