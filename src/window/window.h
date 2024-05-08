#pragma once

#include <string>
#include <memory>

#include <context/renderer.h>

class OpenGLRenderer;
class ImGuiRenderer;
class PixelRenderer;

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

    bool mIsRunning;
};