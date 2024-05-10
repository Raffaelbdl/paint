#pragma once

#include "GL/glew.h"
#include "GL/gl.h"
#include "GLFW/glfw3.h"

#include "imgui_impl_opengl3.h"
#include "imgui_impl_glfw.h"

#include "imgui_context.h"
#include "window/opengl_window.h"

class OpenGL3GlfwImGuiContext : public ImGuiContext
{
public:
    bool init(IWindow *window) override;
    void pre_render() override;
    void post_render() override;
    void end() override;

    OpenGLWindow *get_parent_window() const { return (OpenGLWindow *)window; }
    GLFWwindow *get_window() { return ((OpenGLWindow *)window)->get_window(); }

    const int get_width() const { return get_parent_window()->width; }
    const int get_height() const { return get_parent_window()->height; }
};