#pragma once
#include "BossState.h"
class KnightState :
    public BossState
{
public:
    KnightState(Boss* boss, BossStateMachine* stateMachine, wstring texture)
        : BossState(boss, stateMachine, texture) {}
    virtual ~KnightState() {}
public:
    void Enter() override;
    void UpdateState() override;
    void Exit() override;
};

