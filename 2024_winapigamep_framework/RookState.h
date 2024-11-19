#pragma once
#include "BossState.h"
class RookState :
    public BossState
{
public:
    RookState(Boss* boss, BossStateMachine* stateMachine, wstring texture)
        : BossState(boss, stateMachine, texture) {}
    ~RookState() {}
public:
    void Enter() override;
    void UpdateState() override;
    void Exit() override;
private:
    void StartRoutine();
    void AttackRoutine();
    void EndRoutine();
private:
    bool isStart = false;
    bool isAttack = false;
    bool isEnd = false;
};

