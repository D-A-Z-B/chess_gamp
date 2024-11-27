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
public:
    void StartAttackRoutine(Vec2 size, float duration);
private:
    void AttackRoutine();
private:
    bool isAttack = false;
    Vec2 targetSize;
    float targerDuration;
};

