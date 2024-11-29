#include "pch.h"
#include "KingState.h"

#include "Boss.h"
#include "KingAttackObject.h"
#include "Scene.h"

#include "TimeManager.h"
#include "SceneManager.h"
#include "PlayerManager.h"

void KingState::Enter()
{
	__super::Enter();

	cout << "King State Enter" << endl;

	isAttack = true;

}

void KingState::UpdateState()
{
	__super::UpdateState();

	//__super::boss->SetPos({SCREEN_WIDTH / 2, 250});

	if (isAttack) {
		AttackRoutine();
	}
	else if (isEnd) {
		EndRoutine();
	}
}

void KingState::Exit()
{
	cout << "King State Exit" << endl;
	__super::Exit();
}

void KingState::AttackRoutine()
{
	static int currentAttackCount = 0;
	int attackCount = 4;

	static float moveElapsedTime = 0;
	int moveTime = 1.f;

	static float attackElapsedTime = 0;
	float attackTime = 0.5f;

	static float waitElapsedTime = 0;
	float waitTime = 0.2f;

	static bool isWait = true;
	static bool isMove = false;
	static bool isAttack = false;
	static bool isRefresh = true;

	static Vec2 startPos;
	static Vec2 endPos;

	if (currentAttackCount >= attackCount) {
		isEnd = true;
		this->isAttack = false;

		currentAttackCount = 0;

		return;
	}

	if (isRefresh) {
		Vec2 vPos = __super::boss->GetPos();
		startPos = { vPos.x, 300.f };

		float x = GET_SINGLE(PlayerManager)->GetPlayer()->GetPos().x;

		endPos = { x, 300.f };

		isRefresh = false;
	}

	if (isWait) {
		if (waitElapsedTime < waitTime) {

			waitElapsedTime += fDT;
		}
		else {
			isWait = false;
			isMove = true;

			waitElapsedTime = 0;
		}
	}
	
	if (isMove) {
		if (moveElapsedTime < moveTime) {
			float t = moveElapsedTime / moveTime;

			float calcT = t; // 나중에 이징 넣을거임

			float x = startPos.x * (1 - calcT) + endPos.x * calcT;
			float y = startPos.y * (1 - calcT) + endPos.y * calcT;

			__super::boss->SetPos({ x, y });

			moveElapsedTime += fDT;
		}
		else {
			isMove = false;
			isAttack = true;

			moveElapsedTime = 0;
		}
	}

	if (isAttack) {
		static bool alreadyCreated = false;

		if (alreadyCreated == false) {
			CreateAttackObject({ 500, 500 }, attackTime);

			alreadyCreated = true;
		}

		if (attackElapsedTime < attackTime) {

			attackElapsedTime += fDT;
		}
		else {
			isAttack = false;
			isWait = true;
			isRefresh = true;

			alreadyCreated = false;

			attackElapsedTime = 0;

			currentAttackCount++;
		}
	}
}

void KingState::EndRoutine()
{
	static float endRoutineElapsedTime = 0;
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
		isEnd = false;

		__super::boss->SetPos(endPos);

		endRoutineElapsedTime = 0;

		stateMachine->ChangeState(BOSS_STATE::PAWN);
	}
}

void KingState::CreateAttackObject(Vec2 size, float duration)
{
	KingAttackObject* attackObject = new KingAttackObject();

	Vec2 vPos = __super::boss->GetPos();

	attackObject->SetPos({ vPos.x, vPos.y + 30});
	attackObject->StartAttackRoutine({ 500, 500 }, duration);

	GET_SINGLE(SceneManager)->GetCurrentScene()->AddObject(attackObject, LAYER::BOSS_ATTACK_OBJECT);
}
