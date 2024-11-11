#pragma once
#include "BossState.h"

class PawnState : public BossState
{
public:
    PawnState(Boss* boss, BossStateMachine* stateMachine, wstring texture)
        : BossState(boss, stateMachine, texture) {}
    virtual ~PawnState() {}
    void Enter() override;
    void UpdateState() override;
    void Exit() override;
};
