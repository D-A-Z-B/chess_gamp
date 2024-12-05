#pragma once

#include "Object.h"
#include "StateMachine.h"
#include "ResourceManager.h"

class Texture;
class Boss :
    public Object
{
public:
	Boss();
	~Boss();
public:
	void Initialize();
public:
	void Update() override;
	void Render(HDC _hdc) override;
private:
	void ComponentInitialize();
public:
	virtual void EnterCollision(Collider* _other);
	virtual void StayCollision(Collider* _other);
	virtual void ExitCollision(Collider* _other);
public:
	StateMachine<BOSS_STATE>* stateMachine;
public:
	void SetBossTexture(wstring texture) { m_pTex = GET_SINGLE(ResourceManager)->TextureLoad(texture, L"Texture\\Boss\\" + texture + L".bmp"); }
public:
	void SetPatternDelayTime(float time) {
		patternDelayTime = time;
	}
	float GetPatternDelayTime() {
		return patternDelayTime;
	}

private:
	BOSS_STATE currentStateEnum;
public:
	BOSS_STATE GetCurrentStateEnum() {
		return currentStateEnum;
	}
	void SetCurrentStateEnum(BOSS_STATE newStateEnum) {
		currentStateEnum = newStateEnum;
	}
public :
	void ApplyDamage();
private:
	int m_hp;
	float patternDelayTime = 0;
	Texture* m_pTex;
};

