#pragma once
#include "Object.h"

class Texture;
class Portal :
    public Object
{
public:
	Portal();
	~Portal();
public:
	void Init();
    void Update() override;
    void Render(HDC _hdc) override;
private:
	void ClearRoutine();
public:
	virtual void EnterCollision(Collider* _other);
	virtual void StayCollision(Collider* _other);
	virtual void ExitCollision(Collider* _other);
private:
	Texture* m_pTex;
	bool isClear = false;
};

