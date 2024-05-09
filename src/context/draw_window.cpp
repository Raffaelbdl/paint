#include "context/renderer.h"
#include "renderer.h"

#include <iostream>

bool within_(float v, float a, float b)
{
    return v >= a && v <= b;
}
bool within_(ImVec2 screenPos, ImVec2 winPos, ImVec2 winSize)
{
    if (!within_(screenPos.x, winPos.x, winPos.x + winSize.x))
        return false;
    if (!within_(screenPos.y, winPos.y, winPos.y + winSize.y))
        return false;
    return true;
}

Pixel cursor_to_win_pos_(ImVec2 screenPos, ImVec2 winPos, ImVec2 winSize, float *col)
{
    int x = (int)(std::clamp(screenPos.x, winPos.x, winPos.x + winSize.x) - winPos.x);
    int y = (int)(winSize.y - std::clamp(screenPos.y, winPos.y, winPos.y + winSize.y) + winPos.y);
    float xgl = inv_lerp(screenPos.x, winPos.x, winPos.x + winSize.x);
    xgl = xgl * 2 - 1;
    float ygl = inv_lerp(screenPos.y, winPos.y, winPos.y + winSize.y);
    ygl = ygl * 2 - 1;
    return Pixel{x, y, xgl, ygl, col[0], col[1], col[2]};
}

DrawScene::DrawScene()
{
}

DrawScene::~DrawScene()
{
    delete pixel_buffer;
    delete frame_buffer;
    delete brush_manager;
}

bool DrawScene::init(GLWindow *window)
{
    Renderer::init(window);
    size = ImVec2((float)window->width, (float)window->height);

    brush_manager = new BrushManager();

    pixel_buffer = new GLubyte[window->width * window->height * 3];
    std::fill_n(pixel_buffer, window->width * window->height * 3, (int)(255 * clear_col[0]));

    frame_buffer = new FrameBuffer(window->width, window->height);

    return true;
}

void DrawScene::pre_render()
{
    ImGuiWindowFlags flags = ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoTitleBar;
    bool popen = true;

    ImGuiIO &io = ImGui::GetIO();
    ImGui::SetNextWindowSize(io.DisplaySize);
    ImGui::SetNextWindowPos(ImGui::GetMainViewport()->Pos);

    // Removed padding as it resulted in a shift between the
    // mouse and the result displayed
    ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2());
    ImGui::Begin("Draw Window", &popen, flags);
    {
        ImGui::BeginChild("Render", ImVec2(), ImGuiChildFlags_AlwaysUseWindowPadding);
        {
            ImVec2 winPos = ImGui::GetWindowPos();
            ImVec2 winSize = ImGui::GetWindowSize();
            ImVec2 screenPos = ImGui::GetMousePos();

            Pixel pix = cursor_to_win_pos_(screenPos, winPos, winSize, cur_col);
            bool _within = within_(screenPos, winPos, winSize);

            // Only draw when focused
            bool is_focused = ImGui::IsWindowFocused();
            // Draw On Button Down
            if (is_focused && ImGui::IsMouseDown(ImGuiMouseButton(0)) && _within)
            {
                brush_manager->Draw(pixel_buffer, pix.x, pix.y, Color{cur_col[0], cur_col[1], cur_col[2]}, winSize.x, winSize.y);
            }

            frame_buffer->bind();
            glDrawPixels(size.x, size.y, GL_RGB, GL_UNSIGNED_BYTE, pixel_buffer);

            // Draw Preview
            if (_within)
                brush_manager->DrawPreview(pixel_buffer, pix.x, pix.y, Color{cur_col[0], cur_col[1], cur_col[2]}, winSize.x, winSize.y);

            frame_buffer->unbind();

            ImGui::Image(
                (ImTextureID)frame_buffer->get_frame_texture(),
                ImGui::GetContentRegionAvail(),
                ImVec2(0, 1),
                ImVec2(1, 0));
        }
        ImGui::EndChild();
    }
    ImGui::End();
    ImGui::PopStyleVar();

    ImGui::Begin("Tool Window");
    {
        // Size Option
        ImGui::SliderInt("Size", &brush_manager->size, 1, 250);

        // Brush Option
        for (int n = 0; n < brush_manager->get_num_brushes(); n++)
        {
            char buf[32];
            sprintf(buf, "Brush %d", n);
            if (ImGui::Selectable(buf, cur_brush_id == n))
            {
                cur_brush_id = n;
                brush_manager->set_current_brush(n);
            }
        }

        // Color Option
        ImGui::PushItemWidth(100);
        ImGui::ColorPicker4("Color", cur_col);
    }
    ImGui::End();
}

void DrawScene::post_render()
{
}

void DrawScene::end()
{
}
