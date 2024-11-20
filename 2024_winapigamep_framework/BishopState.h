#pragma once
#include "BossState.h"
class BishopState :
    public BossState
{
public:
    BishopState(Boss* boss, BossStateMachine* stateMachine, wstring texture)
        : BossState(boss, stateMachine, texture) {}
    ~BishopState() {}
public:
    void Enter() override;
    void UpdateState() override;
    void Exit() override;
private:
    void MoveRoutine();
    void AttackRoutine();
    void EndRoutine();
private:
    bool isMove;
    bool isAttack;
    bool isEnd;
};

