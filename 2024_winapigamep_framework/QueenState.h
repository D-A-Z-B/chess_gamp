#pragma once
#include "BossState.h"
class QueenState :
    public BossState
{
public:
    QueenState(Boss* boss, StateMachine<BOSS_STATE>* stateMachine, wstring texture)
        : BossState(boss, stateMachine, texture) {}
    ~QueenState() {}
public:
    void Enter() override;
    void UpdateState() override;
    void Exit() override;
public:
    void AttackRoutine();
    void EndRoutine();
private:
    void CreateProjectile(int idx, Vec2 dir);
private:
    bool isAttack;
    bool isEnd;
    bool isRefresh = true;

    int currentAttackCount = 0;
};