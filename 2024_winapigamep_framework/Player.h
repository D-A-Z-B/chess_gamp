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
	Vec2 m_speed = {0,0};
};

