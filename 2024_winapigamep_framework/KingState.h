#pragma once
#include "BossState.h"
class KingState :
    public BossState
{
public:
    KingState(Boss* boss, StateMachine<BOSS_STATE>* stateMachine, wstring texture)
        : BossState(boss, stateMachine, texture) {}
    ~KingState() {}
public:
    void Enter() override;
    void UpdateState() override;
    void Exit() override;
private:
    void StartRoutine();
    void AttackRoutine();
    void EndRoutine();
    void CreateAttackObject();
private:
    bool isStart;
    bool isAttack;
    bool isEnd;
};

