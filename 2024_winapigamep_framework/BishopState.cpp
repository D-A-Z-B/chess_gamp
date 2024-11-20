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
        float attackTime = 0.9f;

        static float waitElapsedTime = 0;
        float waitTime = 0.2f;

        static bool isAttack = false;
        static bool isWait = true;
        static bool isRefresh = true;
        static bool isTopDown = true; // 위에서 아래로

        static Vec2 startPos;
        static Vec2 endPos;

        if (isRefresh) {
            if (isTopDown) {
                startPos.y = -200;
            }
            else {
                startPos.y = SCREEN_HEIGHT + 200;
            }

            startPos.x = rand() % 1280;
            Vec2 playerPos = GET_SINGLE(PlayerManager)->GetPlayer()->GetPos();
            Vec2 dir = playerPos - startPos;
            dir.Normalize();
            endPos = playerPos + dir * (sqrt(pow(SCREEN_WIDTH, 2) + pow(SCREEN_HEIGHT, 2)));

            __super::boss->SetPos(startPos);
            isTopDown = !isTopDown;
            isRefresh = false;
        }

        if (waitElapsedTime < waitTime && isWait) {
            float t = waitElapsedTime / waitTime;

            waitElapsedTime += fDT;
        }
        else if (waitElapsedTime > waitTime && isWait) {
            isWait = false;
            isAttack = true;
            waitElapsedTime = 0;
        }

        if (attackElapsedTime < attackTime && isAttack) {
            float t = attackElapsedTime / attackTime;

            float calcT = sqrt(1 - pow(t - 1, 2));

            float x = startPos.x * (1 - calcT) + endPos.x * calcT;
            float y = startPos.y * (1 - calcT) + endPos.y * calcT;

            __super::boss->SetPos({ x, y });

            attackElapsedTime += fDT;
        }
        else if (attackElapsedTime > attackTime && isAttack) {
            attackElapsedTime = 0;

            isAttack = false;
            isWait = true;
            isRefresh = true;
        }
    }

void BishopState::EndRoutine()
{
}
