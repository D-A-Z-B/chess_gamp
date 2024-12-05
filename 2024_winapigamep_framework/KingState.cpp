#include "pch.h"
#include "KingState.h"

#include "Boss.h"
#include "KingAttackObject.h"
#include "Scene.h"

#include "TimeManager.h"
#include "SceneManager.h"
#include "PlayerManager.h"
#include "ResourceManager.h"
#include "CameraManager.h"

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
	int moveTime = 3.f;

	static float attackElapsedTime = 0;
	float attackTime = 1.f;

	static float waitElapsedTime = 0;
	float waitTime = 0.5f;

	static float attackWaitElapsedTime = 0;
	float attackWaitTime = 0.55f;

	static float decreaseElapsedTime = 0;
	float decreaseTime = attackTime / 2;

	static bool isWait = true;
	static bool isMove = false;
	static bool isAttackWait = false;
	static bool isAttack = false;
	static bool isDecrease = false;

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

	if (currentAttackCount >= attackCount) {
		isEnd = true;
		this->isAttack = false;

		currentAttackCount = 0;

		return;
	}
	
	if (isMove) {
		static bool isSoundPlay = false;
		if (isSoundPlay == false) {
			GET_SINGLE(ResourceManager)->Play(L"KingMove", SOUND_CHANNEL::BOSS);

			isSoundPlay = true;
		}

		float targetX = GET_SINGLE(PlayerManager)->GetPlayer()->GetPos().x;

		Vec2 startPos = __super::boss->GetPos();
		Vec2 endPos = { targetX, 300.f };

		float followSpeed = 0.03f;

		float x = startPos.x + (endPos.x - startPos.x) * followSpeed;
		float y = startPos.y + (endPos.y - startPos.y) * followSpeed;

		__super::boss->SetPos({ x, y });

		moveElapsedTime += fDT;

		if (moveElapsedTime >= moveTime) {
			isMove = false;
			isAttackWait = true;
			isSoundPlay = false;
			moveElapsedTime = 0;
		}
	}

	if (isAttackWait) {
		if (attackWaitElapsedTime < attackWaitTime) {

			attackWaitElapsedTime += fDT;
		}
		else {
			isAttackWait = false;
			isAttack = true;
			attackWaitElapsedTime = 0;
		}
	}


	if (isAttack) {
		static bool alreadyCreated = false;

		static bool isSoundPlay = false;
		static bool isShaked = false;

		if (isSoundPlay == false) {
			GET_SINGLE(ResourceManager)->Play(L"KingAttack", SOUND_CHANNEL::BOSS);

			isSoundPlay = true;
		}

		if (isShaked == false) {
			GET_SINGLE(CameraManager)->Shake(50, 0.1f);
			isShaked = true;
		}

		if (alreadyCreated == false) {
			CreateAttackObject({ 500, 500 }, attackTime);

			alreadyCreated = true;
		}

		if (attackElapsedTime < attackTime) {

			attackElapsedTime += fDT;
		}
		else {
			isAttack = false;
			isDecrease = true;
			isSoundPlay = false;
			isShaked = false;
			alreadyCreated = false;

			attackElapsedTime = 0;

			currentAttackCount++;
		}
	}

	if (isDecrease) {
		if (decreaseElapsedTime < decreaseTime) {

			decreaseElapsedTime += fDT;
		}
		else {
			isWait = true;
			isDecrease = false;

			decreaseElapsedTime = 0;
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
