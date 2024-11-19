#pragma once
#include "BossState.h"

class PawnState : public BossState
{
public:
    PawnState(Boss* boss, BossStateMachine* stateMachine, wstring texture)
        : BossState(boss, stateMachine, texture) {}
    ~PawnState() {}
public:
    void Enter() override;
    void UpdateState() override;
    void Exit() override;
private:
    void StartRoutine();
    void EndRoutine();
    void Floating();
    void NextPattern();
private:
    bool isFirst = true;
    bool isStart;
    float initialY;
    float floatingAngle = 0;
    float elapsedTime = 0;
    float endRoutineElapsedTime = 0;
};
