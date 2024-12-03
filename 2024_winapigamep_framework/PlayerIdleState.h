#pragma once
#include "PlayerState.h"

class Player;

class PlayerIdleState :
    public PlayerState
{
public:
    PlayerIdleState(Player* player, StateMachine<PLAYER_STATE>* stateMachine, wstring animation)
        : PlayerState(player, stateMachine, animation) { }
    ~PlayerIdleState() {}
public:
    void Enter() override;
    void UpdateState() override;
    void Exit() override;
};

