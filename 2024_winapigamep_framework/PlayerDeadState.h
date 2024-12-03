#pragma once
#include "PlayerState.h"

class Player;

class PlayerDeadState
	: public PlayerState
{
public:
    PlayerDeadState(Player* player, StateMachine<PLAYER_STATE>* stateMachine)
        : PlayerState(player, stateMachine) {
    }
    ~PlayerDeadState() {}
public:
    void Enter() override;
    void UpdateState() override;
    void Exit() override;
};

