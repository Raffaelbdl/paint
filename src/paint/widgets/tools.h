#pragma once

#include "paint/imgui_paint.h"
#include "paint/widgets/widget.h"

class PaintImGui;
class PaintInfo;
class BrushManager;

class ToolBox : public IWidget
{
public:
    bool init(OpenGL3GlfwImGuiContext *context) override;
    void update() override;

    PaintInfo *info();
    BrushManager *brush_manager();
};