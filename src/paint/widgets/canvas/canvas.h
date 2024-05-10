#pragma once

#include <sm.h>

#include "graphics/framebuffer.h"

#include "paint/imgui_paint.h"
#include "paint/widgets/widget.h"
#include "paint/brush/brush.h"

// Forward declaration
class PaintInfo;
class PaintImGui;
class CanvasContext;

float inv_lerp(float v, float a, float b);
float inv_lerp(int v, int a, int b);

class CanvasWidget : public IWidget
{
public:
    CanvasWidget(){};
    ~CanvasWidget();

    bool init(OpenGL3GlfwImGuiContext *context) override;
    void update() override;

    void draw(const int x, const int y, const int width, const int height);

    PaintInfo *info();
    BrushManager *brush_manager();

    const GLubyte *get_pixel_buffer() const { return pixel_buffer; }
    // const bool focused() const { return ((PaintImGui *)context)->get_info()->focused(); }
    // const bool within() const { return ((PaintImGui *)context)->get_info()->within(); }
    // const PixelPos pixel_pos() const { return ((PaintImGui *)context)->get_info()->pixelPos; }
    // const ImVec2 win_size() const { return ((PaintImGui *)context)->get_info()->winSize; }

private:
    GLubyte *pixel_buffer = nullptr;     // Stores user inputs
    FrameBuffer *frame_buffer = nullptr; // Handles rendering
    CanvasContext *sm = nullptr;
};

/// StateMachine for CanvasWidget ///

class CanvasState : public IState
{
public:
    void set_context(CanvasContext *context) { IState::set_context((IContext *)context); }
    CanvasContext *ctx() const
    {
        return (CanvasContext *)context;
    }
};

class IdleState : public CanvasState
{
public:
    void Enter() override {};
    void Update() override;
    void Exit() override {};
};

class OnClickState : public CanvasState
{
public:
    bool ShouldExit();
};

class DrawState : public OnClickState
{
public:
    void Enter() override {};
    void Update() override;
    void Exit() override {};
};

class ColorPickerState : public OnClickState
{
public:
    void Enter() override;
    void Update() override;
    void Exit() override;
};

class CanvasContext : public IContext
{
public:
    CanvasContext()
    {
        idle_state = new IdleState();
        idle_state->set_context(this);

        draw_state = new DrawState();
        draw_state->set_context(this);

        // colorPicker_state = new ColorPickerState();
        // colorPicker_state->set_context(this);

        cur_state = idle_state;
    }
    ~CanvasContext()
    {
        delete idle_state;
        delete draw_state;
        // delete colorPicker_state;
    }

    void set_parent(CanvasWidget *parent) { this->parent = parent; }

public:
    CanvasWidget *parent;

    // States
    IdleState *idle_state;
    DrawState *draw_state;
    // ColorPickerState *colorPicker_state;
};
