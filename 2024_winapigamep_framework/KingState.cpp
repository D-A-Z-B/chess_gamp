#include "pch.h"
#include "KingState.h"

#include "Boss.h"
#include "KingAttackObject.h"
#include "Scene.h"

#include "TimeManager.h"
#include "SceneManager.h"

void KingState::Enter()
{
	__super::Enter();

	cout << "King State Enter" << endl;

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
	int attackCount = 3;

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
		isAttack = false;

		return;
	}

	if (isRefresh) {
		Vec2 vPos = __super::boss->GetPos();
		startPos = { vPos.x, 250.f };

		float randX = rand() % 1400 + 200;

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

			waitElapsedTime += fDT;
		}
		else {
			isAttack = false;
			isWait = true;
			isRefresh = true;

			attackElapsedTime = 0;
		}
	}
}

void KingState::EndRoutine()
{
}

void KingState::CreateAttackObject(Vec2 size, float duration)
{
	KingAttackObject* attackObject = new KingAttackObject();

	Vec2 vPos = __super::boss->GetPos();

	attackObject->SetPos({ vPos.x, vPos.y + 30 });
	attackObject->SetSize({ 500, 500 });

	GET_SINGLE(SceneManager)->GetCurrentScene()->AddObject(attackObject, LAYER::BOSS_ATTACK_OBJECT);
}
