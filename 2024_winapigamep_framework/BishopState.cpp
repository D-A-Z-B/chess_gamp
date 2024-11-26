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
        float attackTime = 2.f;

        static float waitElapsedTime = 0;
        float waitTime = 0.2f;

        static bool isAttack = false;
        static bool isWait = true;
        static bool isRefresh = true;
        static bool isTopDown = true; // 위에서 아래로

        static Vec2 startPos;
        static Vec2 endPos;

        if (currentAttackCount == attackRepeatCount) {
            currentAttackCount = 0;
            isEnd = true;
            this->isAttack = false;
            return;
        }

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

        if (isWait) {
            if (waitElapsedTime < waitTime) {
                float t = waitElapsedTime / waitTime;

                waitElapsedTime += fDT;
            }
            else {
                isWait = false;
                isAttack = true;
                waitElapsedTime = 0;
            }
        }

        if (isAttack) {
            if (attackElapsedTime < attackTime) {
                float t = attackElapsedTime / attackTime;

                float calcT = sqrt(1 - pow(t - 1, 2));

                float x = startPos.x * (1 - calcT) + endPos.x * calcT;
                float y = startPos.y * (1 - calcT) + endPos.y * calcT;

                __super::boss->SetPos({ x, y });

                attackElapsedTime += fDT;
            }
            else {
                attackElapsedTime = 0;

                isAttack = false;
                isWait = true;
                isRefresh = true;
                currentAttackCount++;
            }
        }

    }

void BishopState::EndRoutine()
{
    static float elapsedTime = 0;
    float targetTime = 1.f;

    if (elapsedTime < targetTime) {
        float t = elapsedTime / targetTime;

        elapsedTime += fDT;
    }
    else {
        elapsedTime = 0;
        stateMachine->ChangeState(BOSS_STATE::PAWN);
    }
}
