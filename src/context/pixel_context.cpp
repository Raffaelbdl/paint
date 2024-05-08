#include <iostream>
#include <algorithm>

#include "window/window.h"
#include "context/renderer.h"
#include "renderer.h"

bool within(float v, float a, float b)
{
    return v >= a && v <= b;
}
bool within(ImVec2 screenPos, ImVec2 winPos, ImVec2 winSize)
{
    if (!within(screenPos.x, winPos.x, winPos.x + winSize.x))
        return false;
    if (!within(screenPos.y, winPos.y, winPos.y + winSize.y))
        return false;
    return true;
}

Pixel cursor_to_win_pos(ImVec2 screenPos, ImVec2 winPos, ImVec2 winSize, float *col)
{
    int x = (int)(std::clamp(screenPos.x, winPos.x, winPos.x + winSize.x) - winPos.x);
    int y = (int)(winSize.y - std::clamp(screenPos.y, winPos.y, winPos.y + winSize.y) + winPos.y);
    float xgl = inv_lerp(screenPos.x, winPos.x, winPos.x + winSize.x);
    xgl = xgl * 2 - 1;
    float ygl = inv_lerp(screenPos.y, winPos.y, winPos.y + winSize.y);
    ygl = ygl * 2 - 1;
    return Pixel{x, y, xgl, ygl, col[0], col[1], col[2]};
}

PixelRenderer::PixelRenderer()
{
    brush_manager = new BrushManager();
    cur_brush = brush_manager->get_brush(BrushType::Square);
}

PixelRenderer::~PixelRenderer()
{
    delete pixel_buffer;
    delete brush_manager;
    delete cur_brush;
}

bool PixelRenderer::init(GLWindow *window)
{
    Renderer::init(window);
    pixel_buffer = new GLubyte[window->width * window->height * 3];
    std::fill_n(pixel_buffer, window->width * window->height * 3, (int)(255 * 0.2f));
    return true;
}

void PixelRenderer::pre_render()
{
    ImVec2 winPos = ImGui::GetWindowViewport()->Pos;
    ImVec2 winSize = ImGui::GetMainViewport()->Size;

    ImGui::Begin("test");
    ImVec2 screenPos = ImGui::GetMousePos();
    ImGui::Text("Mouse pos: (%g, %g)", screenPos.x, screenPos.y);
    ImGui::Text("Window pos: (%g, %g)", winPos.x, winPos.y);
    ImGui::Text("Window size: (%g, %g)", winSize.x, winSize.y);
    ImGui::ColorEdit3("Current Color", cur_col);
    ImGui::InputInt("Current Size", &cur_size);
    for (int n = 0; n < 2; n++)
    {
        char buf[32];
        sprintf(buf, "Brush %d", n);
        if (ImGui::Selectable(buf, cur_brush_id == n))
        {
            cur_brush_id = n;

            if (n == 0)
                cur_brush = brush_manager->get_brush(BrushType::Square);
            else
                cur_brush = brush_manager->get_brush(BrushType::Round);
        }
    }
    ImGui::End();

    Pixel pix = cursor_to_win_pos(screenPos, winPos, winSize, cur_col);
    bool _within = within(screenPos, winPos, winSize);

    // Draw On Button Down
    if (ImGui::IsMouseDown(ImGuiMouseButton(0)))
    {
        if (_within)
        {
            cur_brush->Draw(pixel_buffer, pix.x, pix.y, cur_size, Color{cur_col[0], cur_col[1], cur_col[2]}, winSize.x, winSize.y);
        }
    }
    if (ImGui::IsMouseDown(ImGuiMouseButton(1)))
        if (_within)
        {
            cur_brush->Draw(pixel_buffer, pix.x, pix.y, cur_size, Color{clear_col[0], clear_col[1], clear_col[2]}, winSize.x, winSize.y);
        }

    glDrawPixels(mWindow->width, mWindow->height, GL_RGB, GL_UNSIGNED_BYTE, pixel_buffer);

    // Draw Preview
    if (_within)
        cur_brush->DrawPreview(pixel_buffer, pix.x, pix.y, cur_size, Color{cur_col[0], cur_col[1], cur_col[2]}, winSize.x, winSize.y);
}

void PixelRenderer::post_render() {}

void PixelRenderer::end() {}
