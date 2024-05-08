#pragma once

#include <iostream>
#include <memory>

#include <window/window.h>

class Application
{
public:
    Application(const std::string &name);

    void Run();

private:
    std::unique_ptr<GLWindow> mWindow;
};