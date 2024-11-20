#include "pch.h"
#include "BishopState.h"

#include "TimeManager.h"

#include "boss.h"

void BishopState::Enter()
{
	__super::Enter();

    isMove = true;

	cout << "Bishop State Enter" << endl;
}

void BishopState::UpdateState()
{
	__super::UpdateState();

    if (isMove) {
        MoveRoutine();
    }
    else if (isAttack) {
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

void BishopState::MoveRoutine()
{
    static float elapsedTime = 0;
    float targetTime = 2.f;

    static bool isRoutineStart = false;

    static Vec2 startPos;
    static Vec2 endPos;
    static vector<Vec2> endPosV{
        { float(SCREEN_WIDTH) - 100, 100.f },
        { float(SCREEN_WIDTH) - 100, float(SCREEN_HEIGHT) - 200},
        { 100.f, 100.f },
        { 100.f, float(SCREEN_HEIGHT) - 200 },
    };

    static int currentMoveCount = 3;

    if (currentMoveCount >= 4) {
        currentMoveCount = 0;
        isMove = false;
        isEnd = true;
        return;
    }

    if (isRoutineStart == false) {
        startPos = __super::boss->GetPos();
        endPos = endPosV[currentMoveCount];
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
        isMove = false;
        isAttack = true;

        currentMoveCount++;
    }
}

void BishopState::AttackRoutine()
{

}

void BishopState::EndRoutine()
{
}
