#pragma once
#include "PlayerState.h"

class PlayerJumpState :
    public PlayerState
{
public:
    PlayerJumpState(Player* player, StateMachine<PLAYER_STATE>* stateMachine)
        : PlayerState(player, stateMachine) { }
    ~PlayerJumpState() {}
public:
    void Enter() override;
    void UpdateState() override;
    void Exit() override;
private:
    float m_jumpPower = 700.f;
};

