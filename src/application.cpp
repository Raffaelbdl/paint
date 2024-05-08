#include <application.h>

Application::Application(const std::string &name)
{
    mWindow = std::make_unique<GLWindow>();
    mWindow->init(1024, 720, name);
}

void Application::Run()
{
    while (mWindow->is_running())
    {
        mWindow->render();
    }
}