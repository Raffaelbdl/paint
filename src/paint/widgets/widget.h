#pragma once

#include "window/imgui/opengl3_glfw_context.h"

class IWidget
{
public:
    virtual bool init(OpenGL3GlfwImGuiContext *context) = 0;
    virtual void update() = 0;

protected:
    OpenGL3GlfwImGuiContext *context;
};