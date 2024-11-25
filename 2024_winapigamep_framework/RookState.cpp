#include "pch.h"
#include "RookState.h"

#include "TimeManager.h"
#include "PlayerManager.h"

#include "Boss.h"

void RookState::Enter()
{
	__super::Enter();

	isStart = true;

	cout << "Rook State Enter" << endl;
}

void RookState::UpdateState()
{
	__super::UpdateState();

	if (isStart) {
		StartRoutine();
	}
	else if (isAttack) {
		AttackRoutine();
	}
	else if (isEnd) {
		EndRoutine();
	}
}

void RookState::Exit()
{
	__super::Exit();

	cout << "Rook State Exit" << endl;
}

void RookState::StartRoutine()
{
	static float elapsedTime = 0;
    float targetTime = 2.f;

    static bool isRoutineStart = false;

    static Vec2 startPos;
    static Vec2 endPos;

    if (isRoutineStart == false) {
        startPos = __super::boss->GetPos();
        endPos = { float(SCREEN_WIDTH) - 100, 100.f };
        isRoutineStart = true;
    }

    if (elapsedTime < targetTime) {
        float t = elapsedTime / targetTime;
        float calcT = t < 0.5 ? 16 * t * t * t * t * t : 1 - pow(-2 * t + 2, 5) / 2;

        float x = startPos.x * (1 - calcT) + endPos.x * calcT;
        float y = startPos.y * (1 - calcT) + endPos.y * calcT;

        __super::boss->SetPos({ x, y });

        elapsedTime += fDT;
    }
    else {
        elapsedTime = 0;
        isRoutineStart = false;
        isStart = false;
        isAttack = true;
    }
}

void RookState::AttackRoutine()
{
    float followSpeed = 10.f;

    static float FollowElapsedTime = 0;
    float targetTime = 3.f;

    static float attackElapsedTime = 0;
    float attackTime = 0.5f;

    static float waitElapsedTime = 0;
    float waitTime = 0.5f;

    Player* player = GET_SINGLE(PlayerManager)->GetPlayer();

    static bool isFollow = true;
    static bool isWait = false;

    static Vec2 attackStartPos;
    static Vec2 attackEndPos;

    if (isFollow) {
        if (FollowElapsedTime < targetTime) {
            float t = FollowElapsedTime / targetTime;

            float calcT = sqrt(1 - pow(t - 1, 2));

            Vec2 startPos = __super::boss->GetPos();
            Vec2 endPos = { startPos.x, player->GetPos().y };

            float x = startPos.x * (1 - calcT * fDT * followSpeed) + endPos.x * calcT * fDT * followSpeed;
            float y = startPos.y * (1 - calcT * fDT * followSpeed) + endPos.y * calcT * fDT * followSpeed;

            __super::boss->SetPos({ x, y });

            FollowElapsedTime += fDT;
        }
        else {
            FollowElapsedTime = 0;

            isFollow = false;
            isWait = true;

            attackStartPos = __super::boss->GetPos();
            attackEndPos = { -100.f, __super::boss->GetPos().y };
        }
    }

    if (isWait) {
        if (waitElapsedTime < waitTime) {

            waitElapsedTime += fDT;
            return;
        }
        else {
            isWait = false;
            waitElapsedTime = 0;
        }
    }

    if (isFollow == false) {
        if (attackElapsedTime < attackTime) {
            float t = attackElapsedTime / attackTime;

            float calcT = sqrt(1 - pow(t - 1, 2));

            float x = attackStartPos.x * (1 - calcT) + attackEndPos.x * calcT;
            float y = attackStartPos.y * (1 - calcT) + attackEndPos.y * calcT;

            __super::boss->SetPos({ x, y });

            attackElapsedTime += fDT;
        }
        else {
            attackElapsedTime = 0;

            isFollow = true;

            isAttack = false;
            isEnd = true;
        }
    }
}

void RookState::EndRoutine()
{
    static float elapsedTime = 0;
    float targetTime = 2.f;

    if (elapsedTime < targetTime) {
        float t = elapsedTime / targetTime;

        elapsedTime += fDT;
    }
    else {
        elapsedTime = 0;
        stateMachine->ChangeState(BOSS_STATE::PAWN);
    }
}
