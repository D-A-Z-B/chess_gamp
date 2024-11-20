#pragma once
#include "Object.h"
class Texture;
class Player : public Object
{
public:
	Player();
	~Player();
public:
	void Update() override;
	void Render(HDC _hdc) override;
private:
	void CreateProjectile();
private:
	Texture* m_pTex;
	bool m_isJump = false;
	float m_speed = 0;
	float m_jumpPower = 2.f;
	float m_gravity = 9.8f;
	int m_jumpCnt = 0;
};

