#pragma once
#include "Object.h"
class PlayerHealth :
    public Object
{
public:
    void Update() override;
    void Render(HDC _hdc) override;
};

