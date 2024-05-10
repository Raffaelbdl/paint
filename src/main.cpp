#include "application.h"

static constexpr int WIDTH = 1024;
static constexpr int HEIGHT = 720;

int main()
{
    std::unique_ptr<Application> app = std::make_unique<Application>(WIDTH, HEIGHT, "App");
    app->Run();
    return 0;
}