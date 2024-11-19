#pragma once
#include "Player.h"
class PlayerManager
{
	DECLARE_SINGLE(PlayerManager);
public:
	void SetPlayer(Player* player) { this->player = player; };
	Player* GetPlayer() { return player; };
private:
	Player* player;
};

