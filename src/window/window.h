#pragma once

#include <string>
#include <memory>
#include <algorithm>

#include <context/renderer.h>

// Forward declaration of renderers
class OpenGLRenderer;
class ImGuiRenderer;
class PixelRenderer;
class DrawScene;

float inv_lerp(float v, float a, float b);
float inv_lerp(int v, int a, int b);

class GLWindow
{
public:
    GLWindow()
    {
        mIsRunning = true;
        mWindow = nullptr;
        mOpenGLRenderer = std::make_unique<OpenGLRenderer>();
        mImGuiRenderer = std::make_unique<ImGuiRenderer>();
        mPixelRenderer = std::make_unique<PixelRenderer>();
        mDrawScene = std::make_unique<DrawScene>();
    }
    ~GLWindow();

    bool init(int width, int height, const std::string &title);
    void render();

    GLFWwindow *get_window() { return mWindow; }
    void set_window(void *window)
    {
        mWindow = (GLFWwindow *)window;
    }

    bool is_running() { return mIsRunning; }

    int width = 0;
    int height = 0;
    std::string title;

private:
    GLFWwindow *mWindow;

    std::unique_ptr<OpenGLRenderer> mOpenGLRenderer;
    std::unique_ptr<ImGuiRenderer> mImGuiRenderer;
    std::unique_ptr<PixelRenderer> mPixelRenderer;
    std::unique_ptr<DrawScene> mDrawScene;

    bool mIsRunning;
};