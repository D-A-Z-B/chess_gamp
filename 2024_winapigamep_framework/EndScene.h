#pragma once
#include "Scene.h"
class EndScene :
    public Scene
{
public:
    // Scene을(를) 통해 상속됨
    void Init() override;
    virtual void Render(HDC _hdc);
};

