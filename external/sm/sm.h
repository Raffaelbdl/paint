#pragma once

class IContext; // Forward Declaration

class IState
{
public:
    virtual ~IState() {}

    void set_context(IContext *context) { this->context = context; }

    virtual void Enter() = 0;
    virtual void Update() = 0;
    virtual void Exit() = 0;

protected:
    IContext *context;
};

class IContext
{
public:
    virtual void ChangeState(IState *new_state)
    {
        cur_state->Exit();
        cur_state = new_state;
        cur_state->Enter();
    }
    virtual void Update() { cur_state->Update(); };

protected:
    IState *cur_state;
};
