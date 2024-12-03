#pragma once
#include "Object.h"

#include "ResourceManager.h"

class Texture;
class QueenProjectile :
    public Object
{
public:
    QueenProjectile();
    ~QueenProjectile();
public:
    void SetProjectileTexture(wstring texture) { m_pTex = GET_SINGLE(ResourceManager)->TextureLoad(texture, L"Texture\\Boss\\Queen\\" + texture + L".bmp"); }
public:
    void Update() override;
    void Render(HDC _hdc) override;
public:
    virtual void EnterCollision(Collider* _other);
    virtual void StayCollision(Collider* _other);
    virtual void ExitCollision(Collider* _other);
public:
    void Shoot(Vec2 position, Vec2 dir);
private:
    Vec2 m_vDir;
    float speed = 2000.f;
    Texture* m_pTex;
};

