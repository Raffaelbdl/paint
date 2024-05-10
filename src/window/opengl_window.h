#pragma once

#include "window/window.h"

#include "GL/glew.h"
#include "GLFW/glfw3.h"

class OpenGLWindow : public IWindow
{
public:
    ~OpenGLWindow();

    bool init(const int width, const int height, const std::string &title) override;
    void pre_render() override;
    void post_render() override;

    GLFWwindow *get_window() { return (GLFWwindow *)window; }
};