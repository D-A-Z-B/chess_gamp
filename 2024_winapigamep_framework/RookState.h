#pragma once
#include "BossState.h"
class RookState :
    public BossState
{
public:
    RookState(Boss* boss, BossStateMachine* stateMachine, wstring texture)
        : BossState(boss, stateMachine, texture) {}
    virtual ~RookState() {}
public:
    void Enter() override;
    void UpdateState() override;
    void Exit() override;
};

