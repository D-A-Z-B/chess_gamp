#include "pch.h"
#include "KingState.h"

#include "Boss.h"
#include "KingAttackObject.h"
#include "Scene.h"

#include "SceneManager.h"

void KingState::Enter()
{
	__super::Enter();

	cout << "King State Enter" << endl;

}

void KingState::UpdateState()
{
	__super::UpdateState();

	__super::boss->SetPos({SCREEN_WIDTH / 2, 250});
}

void KingState::Exit()
{
	cout << "King State Exit" << endl;
	__super::Exit();
}

void KingState::StartRoutine()
{
}

void KingState::AttackRoutine()
{
}

void KingState::EndRoutine()
{
}

void KingState::CreateAttackObject()
{
	KingAttackObject* attackObject = new KingAttackObject();

	Vec2 vPos = __super::boss->GetPos();

	attackObject->SetPos({ vPos.x, vPos.y + 30 });
	attackObject->SetSize({ 500, 500 });

	GET_SINGLE(SceneManager)->GetCurrentScene()->AddObject(attackObject, LAYER::BOSS_ATTACK_OBJECT);
}
