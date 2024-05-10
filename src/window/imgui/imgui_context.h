#pragma once

#include "imgui.h"

#include "window/window.h"

class ImGuiContext
{
public:
    virtual bool init(IWindow *window)
    {
        this->window = window;
        return true;
    };
    virtual void pre_render() = 0;
    virtual void update() = 0;
    virtual void post_render() = 0;
    virtual void end() = 0;

protected:
    IWindow *window = nullptr;
};