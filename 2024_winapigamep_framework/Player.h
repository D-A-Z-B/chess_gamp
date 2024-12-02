#pragma once
#include "Object.h"
#include "StateMachine.h"
class Texture;
class Player : public Object
{
public:
	Player();
	~Player();
public:
	void Update() override;
	void Render(HDC _hdc) override;
	void SetCurrentStateEnum(PLAYER_STATE newStateEnum) { currentStateEnum = newStateEnum; }
	void ChangePacing(int pacing);
	void ChangeAnimation();
private:
	void CreateProjectile();
	void CheckChangeState();
public:
	StateMachine<PLAYER_STATE>* stateMachine;

	float yVelocity = 0;

	float moveSpeed = 200.f;
	bool isMove = false;

	bool isDash = false;

	int isPacing = 1;
private:
	PLAYER_STATE currentStateEnum;
	Texture* m_pTex;

	float dashCoolTimer = 0;
	float dashCoolTime = 0.5;

	float attackCoolTimer = 0;
	float attackCoolTime = 0.2f;

	float gravity = 9.8f;
};
