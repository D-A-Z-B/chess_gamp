#pragma once
template <typename T>
class State {
public:
    virtual ~State() {}
    virtual void Enter() = 0;
    virtual void UpdateState() = 0;
    virtual void Exit() = 0;
};

