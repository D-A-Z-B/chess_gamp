#pragma once
#include "BossState.h"
class BishopState :
    public BossState
{
public:
    BishopState(Boss* boss, BossStateMachine* stateMachine, wstring texture)
        : BossState(boss, stateMachine, texture) {}
    virtual ~BishopState() {}
public:
    void Enter() override;
    void UpdateState() override;
    void Exit() override;
};

