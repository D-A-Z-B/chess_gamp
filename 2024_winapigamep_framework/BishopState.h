#pragma once
#include "BossState.h"
class BishopState :
    public BossState
{
public:
    BishopState(Boss* boss, StateMachine<BOSS_STATE>* stateMachine, wstring texture)
        : BossState(boss, stateMachine, texture) {}
    ~BishopState() {}
public:
    void Enter() override;
    void UpdateState() override;
    void Exit() override;
private:
    void AttackRoutine();
    void EndRoutine();
private:
    bool isAttack = false;
    bool isEnd = false;
    int currentAttackCount;
};

