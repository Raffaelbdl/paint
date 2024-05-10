#include <cstring>

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include <stb_image_write.h>

#include "paint/imgui_paint.h"
#include "imgui_paint.h"

PaintImGui::PaintImGui()
{
    canvas_widget = new CanvasWidget();
    toolbox = new ToolBox();
    info = new PaintInfo();
    brush_manager = new BrushManager();
}

PaintImGui::~PaintImGui()
{
    delete canvas_widget;
    delete toolbox;
    delete info;
    delete brush_manager;
}

bool PaintImGui::init(IWindow *window)
{
    OpenGL3GlfwImGuiContext::init(window);
    toolbox->init(this);
    canvas_widget->init(this);
    return true;
}

void PaintImGui::update()
{
    canvas_widget->update();
    toolbox->update();
}

void PaintImGui::save()
{
    stbi_flip_vertically_on_write(true);
    char *path = new char[std::strlen(info->save_name) + std::strlen(".png") + 1];
    std::strcpy(path, (info->save_name));
    std::strcat(path, ".png");
    stbi_write_png(path, window->width, window->height, 3, canvas_widget->get_pixel_buffer(), 3 * window->width);
    delete path;
}

void PaintImGui::undo()
{
    canvas_widget->undo();
}

void PaintImGui::redo()
{
    canvas_widget->redo();
}
