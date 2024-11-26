#include "pch.h"
#include "PawnState.h"

#include "TimeManager.h"

#include "Boss.h"
#include "Collider.h"

void PawnState::Enter()
{
	__super::Enter();

    __super::boss->SetCurrentStateEnum(BOSS_STATE::PAWN);

	Vec2 vSize = __super::boss->GetSize();
	__super::boss->GetComponent<Collider>()->SetOffSetPos({ 0.f, vSize.y / 4 });
	__super::boss->GetComponent<Collider>()->SetSize({ vSize.x, vSize.y / 2});

    elapsedTime = 0.f;

    isStart = true;


    if (isFirst) {
        initialY = __super::boss->GetPos().y;
    }
    floatingAngle = 0;
	cout << "Pawn State Enter" << endl;
}

void PawnState::UpdateState() {
    __super::UpdateState();

    if (isStart && isFirst == false) {
        StartRoutine();
    }
    else if (elapsedTime < __super::boss->GetPatternDelayTime()) {
        Floating();
        elapsedTime += fDT;
    }
    else {
        EndRoutine();
    }
}

void PawnState::Exit()
{
	cout << "Pawn State Exit" << endl;
    isFirst = false;
	__super::Exit();
}

void PawnState::StartRoutine() {
    static float elapsedTime = 0;
    float targetTime = 2.f;

    static bool isRoutineStart = false;

    static Vec2 startPos;
    static Vec2 endPos;

    if (isRoutineStart == false) {
        startPos = __super::boss->GetPos();
        endPos = { SCREEN_WIDTH / 2.f, 150.f };
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
        __super::boss->SetPos(endPos);

        elapsedTime = 0;
        isRoutineStart = false;
        isStart = false;
    }
}

void PawnState::EndRoutine() {
    float targetTime = 2.f;

    static bool isEndRoutineStart = false;

    static Vec2 startPos;
    static Vec2 endPos;

    if (isEndRoutineStart == false) {
        startPos = __super::boss->GetPos();
        endPos = { float(SCREEN_WIDTH) + 150, 150.f };
        isEndRoutineStart = true;
    }

    if (endRoutineElapsedTime < targetTime) {
        float t = endRoutineElapsedTime / targetTime;
        float calcT = t < 0.5 ? 16 * t * t * t * t * t : 1 - pow(-2 * t + 2, 5) / 2;

        float x = startPos.x * (1 - calcT) + endPos.x * calcT;
        float y = startPos.y * (1 - calcT) + endPos.y * calcT;

        __super::boss->SetPos({ x, y });

        endRoutineElapsedTime += fDT;
    }
    else {
        isEndRoutineStart = false;
        NextPattern();

        __super::boss->SetPos(endPos);
    }
}

void PawnState::Floating() {
    static int amplitude = 30;
    static double speed = 1.5f;

    Vec2 vPos = __super::boss->GetPos();
    vPos.y = initialY + static_cast<int>(amplitude * sin(floatingAngle));

    floatingAngle += speed * fDT;

    __super::boss->SetPos(vPos);
}

void PawnState::NextPattern() {
    static bool isSeedSet = false;
    if (!isSeedSet) {
        srand(static_cast<unsigned int>(time(0)));
        isSeedSet = true;
    }

    int randNum;
    do {
        randNum = rand() % 6;

    } while (static_cast<BOSS_STATE>(randNum) == BOSS_STATE::PAWN);


    endRoutineElapsedTime = 0;
    stateMachine->ChangeState(BOSS_STATE::KING);
    __super::boss->SetCurrentStateEnum(static_cast<BOSS_STATE>(randNum));
    //stateMachine->ChangeState(static_cast<BOSS_STATE>(randNum));
}

