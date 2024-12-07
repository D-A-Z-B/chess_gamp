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
	void ChangeAnimation(wstring changeAnimation, bool isRepeat);
	void SetDead();
private:
	void CreateProjectile();
	void CheckChangeState();
public:
	StateMachine<PLAYER_STATE>* stateMachine;
	PLAYER_STATE currentStateEnum;
	float yVelocity = 0;
	float moveSpeed = 200.f;
	bool isDash = false;
	int isPacing = 1;
private:
	Texture* m_pTex;
	Texture* m_pDeadTex;
	Texture* m_pFireTex;
	wstring curAnimaton;
	float dashCoolTimer = 0;
	float dashCoolTime = 0.5;
	float fireAnimTimer = 0;
	float fireAnimTime = 0.2f;
	float gravity = 9.8f;
	bool isShooting = false;
	bool isDead = false;
};
