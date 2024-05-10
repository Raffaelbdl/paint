#pragma once

struct PixelPos
{
    int x, y;
    constexpr PixelPos() : x(0), y(0) {}
    constexpr PixelPos(int _x, int _y) : x(_x), y(_y) {}
};

struct Color
{
    float r, g, b;
};