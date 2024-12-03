#pragma once
#include "Object.h"
class Texture;
class Projectile : public Object
{
public:
	Projectile();
	~Projectile();
	void Update() override;
	void Render(HDC _hdc) override;
public:
	void SetAngle(float _f);
	void SetDir(Vec2 _dir)
	{
		m_vDir = _dir;
		m_vDir.Normalize();
	}
private:
	void Rotate(float m_angle);
public:
	virtual void EnterCollision(Collider* _other);
	virtual void StayCollision(Collider* _other);
	virtual void ExitCollision(Collider* _other);
private:
	HDC m_memDC;
	Vec2 m_vDir;
	Texture* m_pTex;

	float m_angle;
	float m_speed = 1000.f;

	long maxX;
	long maxY;
	long minX;
	long minY;
};

