#include <iostream>
#include <context/renderer.h>

float clip(float v, float a, float b)
{
    if (v <= a)
        return a;
    if (v >= b)
        return b;
    return v;
}

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

float inv_lerp(float v, float a, float b)
{
    v = clip(v, a, b);
    return (v - b) / (a - b);
}

// [0, 1] -> [-1, 1]
float ratio_to_coord(float t)
{
    return t * 2.0f - 1.0f;
}

Pixel cursor_to_win_pos(ImVec2 screenPos, ImVec2 winPos, ImVec2 winSize, float *col)
{
    int x = (int)(clip(screenPos.x, winPos.x, winPos.x + winSize.x) - winPos.x);
    int y = (int)(clip(screenPos.y, winPos.y, winPos.y + winSize.y) - winPos.y);
    float xgl = inv_lerp(screenPos.x, winPos.x, winPos.x + winSize.x);
    xgl = xgl * 2 - 1;
    float ygl = inv_lerp(screenPos.y, winPos.y, winPos.y + winSize.y);
    ygl = ygl * 2 - 1;
    return Pixel{x, y, -xgl, ygl, col[0], col[1], col[2]};
}

bool PixelRenderer::init(GLWindow *window)
{
    Renderer::init(window);
    // pixels = std::vector<std::vector<Pixel>>();
    for (int i = 0; i < window->height; i++)
    {
        std::vector<Pixel> row{};
        for (int j = 0; j < window->width; j++)
        {
            row.push_back(Pixel{i, j, clear_col[0], clear_col[1], clear_col[2]});
        }
        pixels.push_back(row);
    }

    // std::cout << pixels.size() << " " << pixels[0].size() << "\n";

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
    ImGui::End();

    if (ImGui::IsMouseDown(ImGuiMouseButton(0)))
    {
        if (within(screenPos, winPos, winSize))
        {
            Pixel pix = cursor_to_win_pos(screenPos, winPos, winSize, cur_col);
            pixels[pix.y][pix.x] = pix;
        }
    }
    if (ImGui::IsMouseDown(ImGuiMouseButton(1)))
        if (within(screenPos, winPos, winSize))
        {
            Pixel pix = cursor_to_win_pos(screenPos, winPos, winSize, clear_col);
            pixels[pix.y][pix.x] = pix;
        }

    glPointSize(2);
    glBegin(GL_POINTS);

    for (std::vector<Pixel> rows : pixels)
    {
        for (Pixel pix : rows)
        {
            glColor3f(pix.r, pix.g, pix.b);
            glVertex2f(pix.xgl, pix.ygl);
        }
    }

    glEnd();
}

void PixelRenderer::post_render() {}

void PixelRenderer::end() {}
