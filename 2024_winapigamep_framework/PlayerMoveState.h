#pragma once
#include "PlayerState.h"

class PlayerMoveState :
    public PlayerState
{
public:
    PlayerMoveState(Player* player, StateMachine<PLAYER_STATE>* stateMachine)
        : PlayerState(player, stateMachine) { }
    ~PlayerMoveState() {}
public:
    void Enter() override;
    void UpdateState() override;
    void Exit() override;
private:
    float m_moveSpeed = 200.f;
};

