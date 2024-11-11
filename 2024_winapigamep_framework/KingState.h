#pragma once
#include "BossState.h"
class KingState :
    public BossState
{
public:
    KingState(Boss* boss, BossStateMachine* stateMachine, wstring texture)
        : BossState(boss, stateMachine, texture) {}
    virtual ~KingState() {}
public:
    void Enter() override;
    void UpdateState() override;
    void Exit() override;
};

