#pragma once

#include <iostream>
#include <memory>

#include "window/opengl_window.h"
#include "paint/imgui_paint.h"

class Application
{
public:
    Application(const int width, const int height, const std::string &name);
    ~Application();

    void Run();

private:
    OpenGLWindow *window;
    PaintImGui *paint_imgui;
};