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

class GLWindow;
class Brush;
class SquareBrush;
class RoundBrush;
class FrameBuffer;

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

private:
    ImVec2 size;

    float cur_col[3] = {0.0f, 0.0f, 0.0f};
    float clear_col[3] = {1.0f, 1.0f, 1.0f};

    int cur_size = 10;
    int cur_brush_id = 0;
    BrushManager *brush_manager;

    GLubyte *pixel_buffer;
    FrameBuffer *frame_buffer;

    char save_path[128];
};