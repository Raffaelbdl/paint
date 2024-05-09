#pragma once

#include <sm.h>

#include "context/renderer.h"

class DrawScene;
class CanvasContext; // Forward

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
    void Enter() override;
    void Update() override;
    void Exit() override;
};

class OnClickState : public CanvasState
{
public:
    bool ShouldExit();
};

class DrawState : public OnClickState
{
public:
    void Enter() override;
    void Update() override;
    void Exit() override;
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

        colorPicker_state = new ColorPickerState();
        colorPicker_state->set_context(this);

        cur_state = idle_state;
    }
    ~CanvasContext()
    {
        delete idle_state;
        delete draw_state;
        delete colorPicker_state;
    }

    void set_scene(DrawScene *scene) { this->scene = scene; }

public:
    DrawScene *scene;

    // States
    IdleState *idle_state;
    DrawState *draw_state;
    ColorPickerState *colorPicker_state;
};
