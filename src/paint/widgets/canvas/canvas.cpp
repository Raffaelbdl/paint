#include <iostream>
#include <algorithm>
#include <iterator>
#include <cstring>
#include <memory>

#include "canvas.h"

static bool within_(float v, float a, float b)
{
    return v >= a && v <= b;
}
static bool within_(ImVec2 screenPos, ImVec2 winPos, ImVec2 winSize)
{
    if (!within_(screenPos.x, winPos.x, winPos.x + winSize.x))
        return false;
    if (!within_(screenPos.y, winPos.y, winPos.y + winSize.y))
        return false;
    return true;
}
float inv_lerp(float v, float a, float b)
{
    v = std::clamp(v, a, b);
    return (v - b) / (a - b);
}
float inv_lerp(int v, int a, int b)
{
    v = std::clamp(v, a, b);
    return float(v - b) / float(a - b);
}

static PixelPos cursor_to_win_pos_(ImVec2 screenPos, ImVec2 winPos, ImVec2 winSize, const float *col)
{
    int x = (int)(std::clamp(screenPos.x, winPos.x, winPos.x + winSize.x) - winPos.x);
    int y = (int)(winSize.y - std::clamp(screenPos.y, winPos.y, winPos.y + winSize.y) + winPos.y);
    // float xgl = inv_lerp(screenPos.x, winPos.x, winPos.x + winSize.x);
    // xgl = xgl * 2 - 1;
    // float ygl = inv_lerp(screenPos.y, winPos.y, winPos.y + winSize.y);
    // ygl = ygl * 2 - 1;
    // return Pixel{x, y, xgl, ygl, col[0], col[1], col[2]};
    return PixelPos{x, y};
}

CanvasWidget::~CanvasWidget()
{
    delete pixel_buffer;
    delete frame_buffer;
    delete sm;
}

bool CanvasWidget::init(OpenGL3GlfwImGuiContext *context)
{
    this->context = context;

    int length = 3 * context->get_width() * context->get_height();
    pixel_buffer = new GLubyte[length];
    size = 3 * context->get_width() * context->get_height() * sizeof(GLubyte);
    std::fill_n(pixel_buffer, length, (int)255); // white background

    frame_buffer = new FrameBuffer(context->get_width(), context->get_height());

    sm = new CanvasContext();
    sm->set_parent(this);

    return true;
}

void CanvasWidget::update()
{
    ImGuiWindowFlags flags = ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoBringToFrontOnFocus;
    bool popen = true;

    ImGuiIO &io = ImGui::GetIO();
    ImGui::SetNextWindowSize(io.DisplaySize);
    ImGui::SetNextWindowPos(ImGui::GetMainViewport()->Pos);

    // Removed padding as it resulted in a shift between the
    // mouse and the result displayed
    ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2());
    ImGui::Begin("Draw Window", &popen, flags);
    {
        ImGui::BeginChild("Canvas", ImVec2(), ImGuiChildFlags_AlwaysUseWindowPadding);
        {
            PaintInfo *info = ((PaintImGui *)context)->get_info();
            // Collect information
            info->winPos = ImGui::GetWindowPos();
            info->winSize = ImGui::GetWindowSize();
            info->mousePos = ImGui::GetMousePos();
            info->pixelPos = cursor_to_win_pos_(info->mousePos, info->winPos, info->winSize, info->cur_col);
            info->set_within(within_(info->mousePos, info->winPos, info->winSize));
            info->set_focused(ImGui::IsWindowFocused());

            sm->Update();

            frame_buffer->bind();
            {
                glDrawPixels(info->winSize.x, info->winSize.y, GL_RGB, GL_UNSIGNED_BYTE, pixel_buffer);

                // Draw Preview
                if (info->within())
                    brush_manager()->DrawPreview(pixel_buffer, info->pixelPos.x, info->pixelPos.y, Color{info->cur_col[0], info->cur_col[1], info->cur_col[2]}, info->winSize.x, info->winSize.y);
            }
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
}

void CanvasWidget::draw(const int x, const int y, const int width, const int height)
{
    float *cur_col = info()->cur_col;
    brush_manager()->Draw(pixel_buffer, x, y, Color{cur_col[0], cur_col[1], cur_col[2]}, width, height);
}

PaintInfo *CanvasWidget::info()
{
    return ((PaintImGui *)context)->get_info();
}
BrushManager *CanvasWidget::brush_manager()
{
    return ((PaintImGui *)context)->get_brush_manager();
}

void CanvasWidget::undo()
{
    if (undo_stack.size() == 0)
        return;

    redo_push_back();

    GLubyte *tmp = undo_stack.back();
    std::copy(tmp, tmp + size, pixel_buffer);

    undo_stack.pop_back();
    delete tmp;
}

void CanvasWidget::undo_push_back()
{
    GLubyte *tmp = new GLubyte[size / sizeof(GLubyte)];
    std::copy(pixel_buffer, pixel_buffer + size, tmp);
    undo_stack.push_back(tmp);
}

void CanvasWidget::redo()
{
    if (redo_stack.size() == 0)
        return;

    undo_push_back();

    GLubyte *tmp = redo_stack.back();
    std::copy(tmp, tmp + size, pixel_buffer);

    redo_stack.pop_back();
    delete tmp;
}

void CanvasWidget::redo_push_back()
{
    GLubyte *tmp = new GLubyte[size / sizeof(GLubyte)];
    std::copy(pixel_buffer, pixel_buffer + size, tmp);
    redo_stack.push_back(tmp);
}

template <typename T>
void delete_pointed_to(T *const ptr)
{
    delete ptr;
}

void CanvasWidget::clear_redo()
{
    std::for_each(redo_stack.begin(), redo_stack.end(), delete_pointed_to<GLubyte>);
    redo_stack.clear();
}