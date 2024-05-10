

#include "tools.h"

bool ToolBox::init(OpenGL3GlfwImGuiContext *context)
{
    this->context = context;
    return true;
}

void ToolBox::update()
{
    ImGui::Begin("ToolWindow");
    {
        // Size Option
        ImGui::SliderInt("Size", &brush_manager()->size, 1, 250);

        // Brush Option
        for (int n = 0; n < brush_manager()->get_num_brushes(); n++)
        {
            char buf[32];
            sprintf(buf, "Brush %d", n);
            if (ImGui::Selectable(buf, info()->cur_brush_id == n))
            {
                info()->cur_brush_id = n;
                brush_manager()->set_current_brush(n);
            }
        }

        // Color Option
        ImGui::PushItemWidth(100);
        ImGui::ColorPicker4("Color", info()->cur_col);

        ImGui::InputText("Save Path", info()->save_name, IM_ARRAYSIZE(info()->save_name));
        ImGui::SameLine();
        if (ImGui::Button("Save"))
        {
            ((PaintImGui *)context)->save();
        }

        if (ImGui::Button("Color picker"))
        {
            info()->set_color_picking(true);
        }
    }
    ImGui::End();
}

PaintInfo *ToolBox::info()
{
    return ((PaintImGui *)context)->get_info();
}

BrushManager *ToolBox::brush_manager()
{
    return ((PaintImGui *)context)->get_brush_manager();
}
