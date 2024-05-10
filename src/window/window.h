#pragma once

#include <string>

class IWindow
{
public:
    virtual bool init(const int width, const int height, const std::string &title) = 0;
    virtual void pre_render() = 0;
    virtual void post_render() = 0;

    const std::string get_title() const { return title; }
    // const int get_width() const { return width; }
    // const int get_height() const { return height; }
    bool is_running() const { return running; }

    int width = 0;
    int height = 0;

protected:
    std::string title = "";

    void *window = nullptr;
    bool running = false;
};