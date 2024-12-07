#pragma once
#include "Scene.h"
class BossTestScene :
    public Scene
{
public:
    virtual void Init() override;
    virtual void Render(HDC _hdc) override;
};

