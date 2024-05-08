#pragma once
#include "context/renderer.h"
#include "types.h"

// Draw a pixel at the given position with the given color
void DrawPixel(
    GLubyte *pixel_buffer,
    int x,
    int y,
    const int size,
    const Color col,
    const int width,
    const int height);

class Brush
{
public:
    virtual void Draw(
        GLubyte *pixel_buffer,
        int x,
        int y,
        const int size,
        const Color col,
        const int width,
        const int height) = 0;
};

class SquareBrush : public Brush
{
public:
    void Draw(
        GLubyte *pixel_buffer,
        int x,
        int y,
        const int size,
        const Color col,
        const int width,
        const int height) override;
};