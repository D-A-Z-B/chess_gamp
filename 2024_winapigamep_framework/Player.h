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
	Vec2 m_speed = { 0, 0 };
	int m_ispacing = 1;

	bool m_isDash = false;
	float m_dashPower = 10.f;
	float m_dashTimer = 0;

	float m_jumpPower = 2.f;
	float m_gravity = 9.8f;
	int m_jumpCnt = 0;
};

