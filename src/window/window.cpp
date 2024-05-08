#include "window/window.h"

GLWindow::~GLWindow()
{
    mOpenGLRenderer->end();
    mImGuiRenderer->end();
}

bool GLWindow::init(int _width, int _height, const std::string &_title)
{
    width = _width;
    height = _height;
    title = _title;

    mOpenGLRenderer->init(this);
    mImGuiRenderer->init(this);
    mPixelRenderer->init(this);

    return mIsRunning;
}

void GLWindow::render()
{
    // Clear the view
    mOpenGLRenderer->pre_render();
    // Init UI
    mImGuiRenderer->pre_render();

    // Test pixel
    mPixelRenderer->pre_render();

    ImGui::ShowDemoWindow();

    // Render UI
    mImGuiRenderer->post_render();
    // Render end, swap buffers
    mOpenGLRenderer->post_render();
}
