#pragma once
#include "Object.h"
class Texture;
class Effect :
    public Object
{
public:
    Effect(EFFECT_TYPE type, float time, bool isReapt);
    ~Effect();
public:
    void Update() override;
    void Render(HDC _hdc) override;
private:
    EFFECT_TYPE type;
    Texture* pTex;

    float time;
    float elapsedTime;

    bool isReapt;
};

