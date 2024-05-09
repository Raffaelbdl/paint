#pragma once

#include <vector>

// GL includes
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

#include "window/window.h"
#include "brush/brush.h"
#include "types.h"

#include "graphics/framebuffer.h"

#include "canvas/canvas.h"

class GLWindow;
class Brush;
class SquareBrush;
class RoundBrush;
class FrameBuffer;
class CanvasContext;

bool within_(float v, float a, float b);
bool within_(ImVec2 screenPos, ImVec2 winPos, ImVec2 winSize);
Pixel cursor_to_win_pos_(ImVec2 screenPos, ImVec2 winPos, ImVec2 winSize, const float *col);

class Renderer
{
public:
    Renderer() { mWindow = nullptr; }
    virtual bool init(GLWindow *window)
    {
        mWindow = window;
        return true;
    }
    virtual void pre_render() = 0;
    virtual void post_render() = 0;
    virtual void end() = 0;

protected:
    GLWindow *mWindow;
};

class OpenGLRenderer : public Renderer
{
public:
    bool init(GLWindow *window) override;
    void pre_render() override;
    void post_render() override;
    void end() override;
};

class ImGuiRenderer : public Renderer
{
public:
    bool init(GLWindow *window) override;
    void pre_render() override;
    void post_render() override;
    void end() override;
};

class PixelRenderer : public Renderer
{
public:
    PixelRenderer();
    ~PixelRenderer();
    bool init(GLWindow *window) override;
    void pre_render() override;
    void post_render() override;
    void end() override;

private:
    GLubyte *pixel_buffer;
    int cur_size = 10;
    float cur_col[3] = {1.0f, 1.0f, 1.0f};
    float clear_col[3] = {1.0f, 1.0f, 1.0f};
    int cur_brush_id = 0;
    Brush *cur_brush;
    BrushManager *brush_manager;

    FrameBuffer *frame_buffer;
};

class DrawScene : public Renderer
{
public:
    DrawScene();
    ~DrawScene();
    bool init(GLWindow *window) override;
    void pre_render() override;
    void post_render() override;
    void end() override;

    const float *get_cur_col() const { return cur_col; }
    void set_cur_col(float *col)
    {
        cur_col[0] = col[0];
        cur_col[1] = col[1];
        cur_col[2] = col[2]; // risk of overflow, use custom struct!
    }

    const GLubyte *get_pixel_buffer() const { return pixel_buffer; }
    const BrushManager *get_brush_manager() const { return brush_manager; }

    void draw(int x, int y, int width, int height);
    bool is_color_picking = false;

    // info class ?
    ImVec2 winPos;
    ImVec2 winSize;
    ImVec2 mousePos;
    Pixel pixel;
    bool within;
    bool is_focused;

private:
    ImVec2 size;

    float cur_col[3] = {0.0f, 0.0f, 0.0f};
    float clear_col[3] = {1.0f, 1.0f, 1.0f};

    int cur_size = 10;
    int tmp_size = 10;
    int cur_brush_id = 0;
    BrushManager *brush_manager;

    GLubyte *pixel_buffer;
    FrameBuffer *frame_buffer;

    char save_path[128];

    CanvasContext *sm;
};