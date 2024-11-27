#pragma once
#include "Object.h"
class KingAttackObject :
    public Object
{
public:
    KingAttackObject();
    ~KingAttackObject();
public:
    void Update() override;
    void Render(HDC _hdc) override;
public:
    virtual void EnterCollision(Collider* _other);
    virtual void StayCollision(Collider* _other);
    virtual void ExitCollision(Collider* _other);
private:
    bool canAttack = false;
};

