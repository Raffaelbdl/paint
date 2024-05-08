#include "application.h"

int main()
{
    std::unique_ptr<Application> app = std::make_unique<Application>("App");
    app->Run();
    return 0;
}