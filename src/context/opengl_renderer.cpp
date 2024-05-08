#include <context/renderer.h>

bool OpenGLRenderer::init(GLWindow *window)
{
    Renderer::init(window);

    // Initialize GLFW
    if (!glfwInit())
    {
        fprintf(stderr, "GLFW not initialized.");
        return false;
    }

    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

    // Create GLFW window
    GLFWwindow *glWindow = glfwCreateWindow(
        mWindow->width, mWindow->height, mWindow->title.c_str(), nullptr, nullptr);
    // Store window for callbacks
    mWindow->set_window(glWindow);

    if (!glWindow)
    {
        fprintf(stderr, "Window not created.");
        return false;
    }

    // Set callbacks
    // https://github.com/jayanam/jgl_demos/blob/3d887e28ee8566ab79365505be2eeff628387d9e/JGL_MeshLoader/source/render/opengl_context.cpp#L52

    glfwMakeContextCurrent(glWindow);
    glfwSwapInterval(1); // Enable vsync

    glewExperimental = GL_TRUE;
    GLenum err = glewInit();
    if (GLEW_OK != err)
    {
        /* Problem: glewInit failed, something is seriously wrong. */
        fprintf(stderr, "Error: %s\n", glewGetErrorString(err));
        return false;
    }

    return true;
}

void OpenGLRenderer::pre_render()
{
    glViewport(0, 0, mWindow->width, mWindow->height);
    glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
}

void OpenGLRenderer::post_render()
{
    glfwPollEvents();
    glfwSwapBuffers((GLFWwindow *)mWindow->get_window());
}

void OpenGLRenderer::end()
{
    glfwDestroyWindow((GLFWwindow *)mWindow->get_window());
    glfwTerminate();
}