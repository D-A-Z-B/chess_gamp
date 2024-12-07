#include "pch.h"
#include "BishopState.h"

#include "TimeManager.h"
#include "PlayerManager.h"
#include "ResourceManager.h"

#include "boss.h"

void BishopState::Enter()
{
	__super::Enter();

    isAttack = true;
    currentAttackCount = 0;

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

    int attackRepeatCount = 4;

    static float attackElapsedTime = 0;
    float attackTime = 2.f;

    static float waitElapsedTime = 0;
    float waitTime = 1.2f;

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

    if (isWait) {
        static bool isSoundPlay = false;
        if (isSoundPlay == false) {
            GET_SINGLE(ResourceManager)->Play(L"Caution", SOUND_CHANNEL::BOSS);

            isSoundPlay = true;
        }

        if (waitElapsedTime < waitTime) {
            float t = waitElapsedTime / waitTime;

            if (waitElapsedTime > 1.f) {
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
            }

            waitElapsedTime += fDT;
        }
        else {

            isWait = false;
            isAttack = true;

            isSoundPlay = false;

            waitElapsedTime = 0;
        }
    }

    if (isAttack) {
        static bool isSoundPlay = false;


        if (isSoundPlay == false) {
            GET_SINGLE(ResourceManager)->Play(L"BossMove_isFast", SOUND_CHANNEL::BOSS);

            isSoundPlay = true;
        }

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

            isSoundPlay = false;

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
