#include "window/opengl_window.h"

OpenGLWindow::~OpenGLWindow()
{
    glfwDestroyWindow((GLFWwindow *)window);
    glfwTerminate();
}

bool OpenGLWindow::init(const int width, const int height, const std::string &title)
{
    this->width = width;
    this->height = height;
    this->title = title;
    this->running = true;

    // Initialize GLFW
    if (!glfwInit())
    {
        fprintf(stderr, "GLFW not initialized.");
        return false;
    }

    // Canvas not resizable
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

    // Create GLFW window
    this->window = glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr);

    if (!this->window)
    {
        fprintf(stderr, "Window not created.");
        return false;
    }

    /* Add close callback here */

    glfwMakeContextCurrent((GLFWwindow *)this->window);
    glfwSwapInterval(1); // Enable vsync

    // Initialize GLEW
    glewExperimental = GL_TRUE;
    GLenum err = glewInit();
    if (GLEW_OK != err)
    {
        fprintf(stderr, "Error: %s\n", glewGetErrorString(err));
        return false;
    }

    return true;
}

void OpenGLWindow::pre_render()
{
    glViewport(0, 0, width, height);
    glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
}

void OpenGLWindow::post_render()
{
    glfwPollEvents();
    glfwSwapBuffers((GLFWwindow *)window);
}
