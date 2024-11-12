#pragma once
#include "BossState.h"
class QueenState :
    public BossState
{
public:
    QueenState(Boss* boss, BossStateMachine* stateMachine, wstring texture)
        : BossState(boss, stateMachine, texture) {}
    ~QueenState() {}
public:
    void Enter() override;
    void UpdateState() override;
    void Exit() override;
};