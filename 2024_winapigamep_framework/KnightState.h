#pragma once
#include "BossState.h"
class KnightState :
    public BossState
{
public:
    KnightState(Boss* boss, StateMachine<BOSS_STATE>* stateMachine, wstring texture)
        : BossState(boss, stateMachine, texture) {}
    ~KnightState() {}
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
    bool isRefresh = true;
    bool isFirst = true;
    int currentAttackCount = 1;
};

