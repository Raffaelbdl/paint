#pragma once

#include "types.h"

#include "window/imgui/opengl3_glfw_context.h"
#include "paint/widgets/canvas/canvas.h"
#include "paint/widgets/tools.h"
#include "paint/brush/brush.h"

// Forward declaration
class CanvasWidget;
class ToolBox;

class PaintInfo
{
public:
    const bool within() const { return _within; }
    void set_within(bool v) { _within = v; }

    const bool focused() const { return _focused; }
    void set_focused(bool v) { _focused = v; }

    const bool color_picking() const { return _color_picking; }
    void set_color_picking(bool v) { _color_picking = v; }

    ImVec2 size{};
    ImVec2 winPos{};
    ImVec2 winSize{};
    ImVec2 mousePos{};
    PixelPos pixelPos{};

        float cur_col[3]{0.0f, 0.0f, 0.0f};
    int cur_brush_id = 0;

    char save_name[128]{};

private:
    bool _within = false;
    bool _focused = false;
    bool _color_picking = false;
};

class PaintImGui : public OpenGL3GlfwImGuiContext
{
public:
    PaintImGui();
    ~PaintImGui();
    bool init(IWindow *window) override;
    void update() override;

    PaintInfo *get_info() { return info; }
    BrushManager *get_brush_manager() { return brush_manager; }

    void save();
    void undo();
    void redo();

private:
    PaintInfo *info = nullptr;
    BrushManager *brush_manager = nullptr;

    CanvasWidget *canvas_widget;
    ToolBox *toolbox;
};