#include <algorithm>
#include <math.h>
#include <iostream>

#include "window/window.h"
#include "paint/widgets/canvas/canvas.h"

#include "brush.h"

// Stores in pixel_buffer
void DrawPixel(
    GLubyte *pixel_buffer,
    int x,
    int y,
    const Color col,
    const int width)
{
    int pos = (x + y * width) * 3;
    pixel_buffer[pos] = (int)(255 * col.r);
    pixel_buffer[pos + 1] = (int)(255 * col.g);
    pixel_buffer[pos + 2] = (int)(255 * col.b);
}

// Does not store in pixel_buffer
void ShowPixel(
    int x,
    int y,
    const Color col,
    const int width,
    const int height)
{
    glColor3f(col.r, col.g, col.b);
    float xgl = -(inv_lerp(x, 0, width) * 2 - 1);
    float ygl = -(inv_lerp(y, 0, height) * 2 - 1);
    glVertex2f(xgl, ygl);
}
void ShowPixel(
    int x,
    int y,
    const int width,
    const int height)
{
    float xgl = -(inv_lerp(x, 0, width) * 2 - 1);
    float ygl = -(inv_lerp(y, 0, height) * 2 - 1);
    glVertex2f(xgl, ygl);
}

void SquareBrush::Draw(
    GLubyte *pixel_buffer,
    int x,
    int y,
    const int size,
    const Color col,
    const int width,
    const int height)
{
    if (size == 1)
    {
        DrawPixel(pixel_buffer, x, y, col, width);
        return;
    }

    int odd_offset = size / 2;
    int evenoffset = size / 2 - 1;
    int leftest = std::clamp(x - odd_offset, 0, width - 1);
    int rightest = std::clamp(x + evenoffset, 0, width - 1);
    int uppest = std::clamp(y - odd_offset, 0, height - 1);
    int lowest = std::clamp(y + evenoffset, 0, height - 1);

    for (int i = leftest; i <= rightest; i++)
    {
        for (int j = uppest; j <= lowest; j++)
        {
            DrawPixel(pixel_buffer, i, j, col, width);
        }
    }
}

void SquareBrush::DrawPreview(GLubyte *pixel_buffer, int x, int y, const int size, const Color col, const int width, const int height)
{
    int odd_offset = size / 2;
    int evenoffset = size / 2 - 1;
    int leftest = std::clamp(x - odd_offset, 0, width - 1);
    int rightest = std::clamp(x + evenoffset, 0, width - 1);
    int uppest = std::clamp(y - odd_offset, 0, height - 1);
    int lowest = std::clamp(y + evenoffset, 0, height - 1);

    glPointSize(1);
    glBegin(GL_POINTS);

    for (int i = leftest; i <= rightest; i++)
    {
        ShowPixel(i, uppest, col, width, height);
        ShowPixel(i, lowest, col, width, height);
    }
    for (int j = uppest; j <= lowest; j++)
    {

        ShowPixel(leftest, j, col, width, height);
        ShowPixel(rightest, j, col, width, height);
    }

    glEnd();
}

void RoundBrush::Draw(
    GLubyte *pixel_buffer,
    int x,
    int y,
    const int size,
    const Color col,
    const int width,
    const int height)
{
    if (size == 1)
    {
        DrawPixel(pixel_buffer, x, y, col, width);
        return;
    }
    int pow_rad = std::pow(size / 2, 2);
    int odd_offset = size / 2;
    int evenoffset = size / 2 - 1;
    int leftest = std::clamp(x - odd_offset, 0, width - 1);
    int rightest = std::clamp(x + evenoffset, 0, width - 1);
    int uppest = std::clamp(y - odd_offset, 0, height - 1);
    int lowest = std::clamp(y + evenoffset, 0, height - 1);

    for (int i = leftest; i <= rightest; i++)
    {
        for (int j = uppest; j <= lowest; j++)
        {
            if (std::pow(i - x, 2) + std::pow(j - y, 2) <= pow_rad)
                DrawPixel(pixel_buffer, i, j, col, width);
        }
    }
}

void RoundBrush::DrawPreview(GLubyte *pixel_buffer, int x, int y, const int size, const Color col, const int width, const int height)
{
    int offset = size / 2;

    // set min to 1 to appear on screen when previewing
    int leftest = std::max(x - offset, 1);
    int rightest = std::min(x + offset, width - 1);
    int uppest = std::max(y - offset, 1);
    int lowest = std::min(y + offset, height - 1);

    glColor3f(col.r, col.g, col.b);
    glBegin(GL_LINE_LOOP);

    int num_segments = 1000;
    float radius = (float)size / 2.0f;
    for (int seg = 0; seg < num_segments; seg++)
    {
        float theta = 2.0f * M_PI * (float)seg / (float)num_segments;
        float i = radius * cosf(theta);
        float j = radius * sinf(theta);
        int xgl = std::clamp(int(x + i), leftest, rightest);
        int ygl = std::clamp(int(y + j), uppest, lowest);
        ShowPixel(xgl, ygl, width, height);
    }

    glEnd();
}

BrushManager::BrushManager()
{
    square_brush = new SquareBrush();
    round_brush = new RoundBrush();
}

BrushManager::~BrushManager()
{
    delete square_brush;
    delete round_brush;
}

Brush *BrushManager::get_current_brush() const
{
    if (cur_brush == 0)
        return square_brush;
    if (cur_brush == 1)
        return round_brush;
    else
        return nullptr;
}

void BrushManager::set_current_brush(int i)
{
    cur_brush = i;
}

void BrushManager::Draw(GLubyte *pixel_buffer, int x, int y, const Color col, const int width, const int height)
{
    get_current_brush()->Draw(pixel_buffer, x, y, size, col, width, height);
}

void BrushManager::DrawPreview(GLubyte *pixel_buffer, int x, int y, const Color col, const int width, const int height)
{
    get_current_brush()->DrawPreview(pixel_buffer, x, y, size, col, width, height);
}
