#pragma once

#include "Object.h"
#include "BossStateMachine.h"

class Boss :
    public Object
{
public:
	Boss();
	~Boss();
public:
	void Update() override;
	void Render(HDC _hdc) override;
public:
	virtual void EnterCollision(Collider* _other);
	virtual void StayCollision(Collider* _other);
	virtual void ExitCollision(Collider* _other);
public:
	BossStateMachine* StateMachine;
private:
	int m_hp;
};

