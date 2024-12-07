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
    void AttackRoutine();
    void EndRoutine();
    void CreateAttackObject(Vec2 size, float duration);
private:
    bool isAttack;
    bool isEnd;

    int currentAttackCount = 0;
};

