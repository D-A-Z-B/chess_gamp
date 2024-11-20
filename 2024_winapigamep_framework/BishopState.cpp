#include "pch.h"
#include "BishopState.h"

#include "TimeManager.h"
#include "PlayerManager.h"

#include "boss.h"

void BishopState::Enter()
{
	__super::Enter();

    isAttack = true;

	cout << "Bishop State Enter" << endl;
}

void BishopState::UpdateState()
{
	__super::UpdateState();

    if (isAttack) {
        AttackRoutine();
    }
    else if (isEnd) {
        EndRoutine();
    }
}

void BishopState::Exit()
{
	cout << "Bishop State Exit" << endl;
	__super::Exit();
}

void BishopState::AttackRoutine()
{
    static int currentAttackCount = 0;
    int attackRepeatCount = 4;

    static float attackElapsedTime = 0;
    float attackTime = 0.5f;

    static float waitElapsedTime = 0;
    float waitTime = 0.5f;

    static bool isWait = false;
    static bool isRefresh = true;
    static bool isTopDown = true; // 위에서 아래로

    static Vec2 startPos;
    static Vec2 endPos;

    if (isRefresh) {
        if (isTopDown) {
            startPos.x = rand() % 1280;
            startPos.y = -200;

            Vec2 playerPos = GET_SINGLE(PlayerManager)->GetPlayer()->GetPos();

        }
        else {

        }
        __super::boss->SetPos(endPos);
        isTopDown = !isTopDown;
        isRefresh = false;
    }
}

void BishopState::EndRoutine()
{
}
