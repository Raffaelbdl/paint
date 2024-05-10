#include <application.h>

Application::Application(const int width, const int height, const std::string &name)
{
    window = new OpenGLWindow();
    window->init(width, height, name);

    paint_imgui = new PaintImGui();
    paint_imgui->init(window);
}

Application::~Application()
{
    delete window;
    delete paint_imgui;
}

void Application::Run()
{
    while (window->is_running())
    {
        window->pre_render();
        paint_imgui->pre_render();

        paint_imgui->update();

        paint_imgui->post_render();
        window->post_render();
    }
}