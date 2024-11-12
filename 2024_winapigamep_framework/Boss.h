#pragma once

#include "Object.h"
#include "BossStateMachine.h"
#include "ResourceManager.h"

class Texture;
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
	void ComponentInitialize();
public:
	virtual void EnterCollision(Collider* _other);
	virtual void StayCollision(Collider* _other);
	virtual void ExitCollision(Collider* _other);
public:
	BossStateMachine* StateMachine;
public:
	void SetBossTexture(wstring texture) { m_pTex = GET_SINGLE(ResourceManager)->TextureLoad(texture, L"Texture\\Boss\\" + texture + L".bmp"); }
private:
	int m_hp;
	Texture* m_pTex;
};

