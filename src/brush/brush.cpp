#include <algorithm>

#include "brush/brush.h"

void DrawPixel(
    GLubyte *pixel_buffer,
    int x,
    int y,
    const int size,
    const Color col,
    const int width,
    const int height)
{
    int pos = (x + y * width) * 3;
    pixel_buffer[pos] = (int)(255 * col.r);
    pixel_buffer[pos + 1] = (int)(255 * col.g);
    pixel_buffer[pos + 2] = (int)(255 * col.b);
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
        DrawPixel(pixel_buffer, x, y, size, col, width, height);
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
            DrawPixel(pixel_buffer, i, j, 1, col, width, height);
        }
    }
}