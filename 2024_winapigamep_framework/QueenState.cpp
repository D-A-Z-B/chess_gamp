#include "pch.h"
#include "QueenState.h"

#include "TimeManager.h"
#include "SceneManager.h"

#include "Scene.h"
#include "Boss.h"
#include "QueenProjectile.h"

void QueenState::Enter()
{
	__super::Enter();

	isAttack = true;
	isEnd = false;

	cout << "Queen State Enter" << endl;
}

void QueenState::UpdateState()
{
	__super::UpdateState();

	if (isAttack) {
		AttackRoutine();
	}
	else if (isEnd) {
		EndRoutine();
	}
}

void QueenState::Exit()
{
	__super::Enter();

	cout << "Queen State Exit" << endl;
}

void QueenState::AttackRoutine()
{
	static int currentAttackCount = 0;
	int attackCount = 4;

	static float waitElapsedTime = 0;
	float waitTime = 0.5f;

	static float moveElapsedTime = 0;
	float moveTime = 0.7f;

	static float attackElapsedTime = 0;
	float attackTime = 0.1f;

	static bool isWait = true;
	static bool isMove = false;
	static bool isAttack = false;

	static Vec2 startPos;
	static Vec2 endPos;

	static bool isRefresh = true;

	if (currentAttackCount == attackCount) {
		this->isAttack = false;
		isEnd = true;

		currentAttackCount = 0;
		return;
	}

	if (isRefresh) {
		Vec2 vPos = __super::boss->GetPos();
		startPos = { vPos.x, 200.f  };

		float randX;

		do {
			randX = rand() % 800 + 200;
		} while (abs(endPos.x - randX) < 400);

		endPos = { randX, 200.f };

		isRefresh = false;
	}

	if (isWait) {
		if (waitElapsedTime < waitTime) {

			waitElapsedTime += fDT;
		}
		else {
			waitElapsedTime = 0;

			isWait = false;
			isMove = true;
		}
	}

	if (isMove) {
		if (moveElapsedTime < moveTime) {
			float t = moveElapsedTime / moveTime;
			float calcT = t ==  0 ? 0 : t == 1 ? 1 : t < 0.5 ? pow(2, 20 * t - 10) / 2 : (2 - pow(2, -20 * t + 10)) / 2;

			float x = startPos.x * (1 - calcT) + endPos.x * calcT;
			float y = startPos.y * (1 - calcT) + endPos.y * calcT;

			__super::boss->SetPos({ x, y });

			moveElapsedTime += fDT;
		}
		else {
			moveElapsedTime = 0;

			isMove = false;
			isAttack = true;
		}
	}

	if (isAttack) {
		vector<int> dx{ 1, -1, 0, 0, 1, 1, -1, -1 }; // 우, 좌, 상, 하, 우상, 우하, 좌상, 좌하
		vector<int> dy{ 0, 0, -1, 1, -1, 1, -1, 1 }; // Y축 방향 반전


		static bool alreadyCreatedProjectile = false;

		if (alreadyCreatedProjectile == false) {

			for (int i = 0; i < 8; ++i) {
				CreateProjectile(i, {dx[i], dy[i]});
			}

			alreadyCreatedProjectile = true;
		}

		if (attackElapsedTime < attackTime) {
			attackElapsedTime += fDT;
		}
		else {
			attackElapsedTime = 0;
			currentAttackCount++;

			isAttack = false;
			isWait = true;
			isRefresh = true;

			alreadyCreatedProjectile = false;
		}
	}
}

void QueenState::EndRoutine()
{
	static float endElapsedTime = 0;
	float endTime = 1.f;

	static float waitElapsedTime = 0;
	float waitTime = 0.5f;

	static Vec2 startPos;
	static Vec2 endPos;
	
	static bool isWait = true;
	static bool isEnd = false;
	static bool isRefresh = true;

	if (isRefresh) {
		startPos = __super::boss->GetPos();
		endPos = { -100, 100 };

		isRefresh = false;
	}

	if (isWait) {
		if (waitElapsedTime < waitTime) {
			waitElapsedTime += fDT;
		}
		else {
			isEnd = true;
			isWait = false;

			waitElapsedTime = 0;
		}
	}

	if (isEnd) {
		if (endElapsedTime < endTime) {
			float t = endElapsedTime / endTime;
			float calcT = t == 0 ? 0 : t == 1 ? 1 : t < 0.5 ? pow(2, 20 * t - 10) / 2 : (2 - pow(2, -20 * t + 10)) / 2;

			float x = startPos.x * (1 - calcT) + endPos.x * calcT;
			float y = startPos.y * (1 - calcT) + endPos.y * calcT;

			__super::boss->SetPos({ x, y });

			endElapsedTime += fDT;
		}
		else {
			endElapsedTime = 0;

			isWait = true;
			isEnd = false;
			isAttack = true;

			isRefresh = true;

			stateMachine->ChangeState(BOSS_STATE::PAWN);
		}
	}
}

void QueenState::CreateProjectile(int idx, Vec2 dir)
{
	QueenProjectile* projectile = new QueenProjectile();
	projectile->SetProjectileTexture(L"sprite_" + std::to_wstring(idx));
	projectile->SetSize({ 300, 300 });

	Vec2 vPos = __super::boss->GetPos();

	projectile->Shoot({vPos.x, vPos.y + 50}, dir);
	GET_SINGLE(SceneManager)->GetCurrentScene()->AddObject(projectile, LAYER::BOSS_PROJECTILE);
}
