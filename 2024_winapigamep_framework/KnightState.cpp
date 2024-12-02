#include "pch.h"
#include "KnightState.h"

#include "TimeManager.h"
#include "CameraManager.h"

#include "Collider.h"
#include "Boss.h"

void KnightState::Enter()
{
	__super::Enter();

	Vec2 vSize = __super::boss->GetSize();

	__super::boss->GetComponent<Collider>()->SetOffSetPos({ 0.f, vSize.y / 4 });
	__super::boss->GetComponent<Collider>()->SetSize({ vSize.x + 50, vSize.y });

	__super::boss->SetSize(vSize * 1.5);

	isAttack = true;

	cout << "Knight State Enter" << endl;
}

void KnightState::UpdateState()
{
	__super::UpdateState();

	if (isAttack) {
		AttackRoutine();
	}
	else if (isEnd) {
		EndRoutine();
	}
}

void KnightState::Exit()
{
	__super::Exit();

	Vec2 vSize = __super::boss->GetSize();

	__super::boss->SetSize(vSize / 1.5);

	cout << "Knight State Exit" << endl;
}

void KnightState::AttackRoutine()
{
    static float moveElapsedTime = 0;
    const float moveTime = 0.2f;

    static float dropElapsedTime = 0;
    const float dropTime = 0.02f;

    static float dropWaitElapsedTime = 0;
    const float dropWaitTime = 0.3f;

    static float waitElapsedTime = 0;
    const float waitTime = 0.3f;

    static int currentAttackCount = 1;

    static bool isMove = true;
    static bool isDropWait = false;
    static bool isDrop = false;
    static bool isWait = false;

    static Vec2 moveStartPos, moveEndPos;
    static Vec2 dropStartPos, dropEndPos;

    static bool isRefresh = true;
    static bool isFirst = true;

    if (currentAttackCount >= 8) {
        isAttack = false;
        isEnd = true;
        isFirst = true;
        currentAttackCount = 0;
        return;
    }

    // 초기화
    if (isRefresh) {
        if (isFirst) {
            moveStartPos = { 1400, 325 };
        }
        else {
            moveStartPos = __super::boss->GetPos();
        }

        moveEndPos = { 200 + (1080 - (1080 / 5) * currentAttackCount), 150 };

        dropStartPos = moveEndPos;
        dropEndPos = { dropStartPos.x, 330.f };

        __super::boss->SetPos(moveStartPos);

        isRefresh = false;
        isFirst = false;
    }

    // 이동
    if (isMove) {
        if (moveElapsedTime < moveTime) {
            float t = moveElapsedTime / moveTime;
            Vec2 newPos = {
                moveStartPos.x * (1 - t) + moveEndPos.x * t,
                moveStartPos.y * (1 - t) + moveEndPos.y * t
            };
            __super::boss->SetPos(newPos);
            moveElapsedTime += fDT;
        }
        else {
            isMove = false;
            isDropWait = true;
            moveElapsedTime = 0;
        }
    }

    // 낙하 대기
    else if (isDropWait) {
        if (dropWaitElapsedTime < dropWaitTime) {
            dropWaitElapsedTime += fDT;
        }
        else {
            isDropWait = false;
            isDrop = true;
            dropWaitElapsedTime = 0;
        }
    }

    // 낙하
    else if (isDrop) {
        if (dropElapsedTime < dropTime) {
            float t = dropElapsedTime / dropTime;
            Vec2 newPos = {
                dropStartPos.x * (1 - t) + dropEndPos.x * t,
                dropStartPos.y * (1 - t) + dropEndPos.y * t
            };
            __super::boss->SetPos(newPos);
            dropElapsedTime += fDT;
        }
        else {
            GET_SINGLE(CameraManager)->Shake(10, 0.1f);

            GET_SINGLE(ResourceManager)->Play(L"TakeDown");

            isDrop = false;
            isWait = true;
            __super::boss->SetPos(dropEndPos);
            dropElapsedTime = 0;
        }
    }

    // 대기
    else if (isWait) {
        if (waitElapsedTime < waitTime) {
            waitElapsedTime += fDT;
        }
        else {
            isWait = false;
            isMove = true;
            isRefresh = true;
            waitElapsedTime = 0;

            currentAttackCount++;
        }
    }
}

void KnightState::EndRoutine()
{
    static float waitElapsedTime = 0;
    float waitTime = 1.f;

    if (waitElapsedTime < waitTime) {
        waitElapsedTime += fDT;
    }
    else {
        isEnd = false;
        isAttack = false;
        waitElapsedTime = 0;
        stateMachine->ChangeState(BOSS_STATE::PAWN);
    }
}
