#pragma once

#include <vector>

// GL includes
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

#include "window/window.h"

struct Pixel
{
    int x, y;
    float xgl, ygl;
    float r, g, b;
};

class GLWindow;

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
    bool init(GLWindow *window) override;
    void pre_render() override;
    void post_render() override;
    void end() override;

private:
    std::vector<std::vector<Pixel>> pixels{};
    float cur_col[3] = {1.0f, 1.0f, 1.0f};
    float clear_col[3] = {0.2f, 0.2f, 0.2f};
};