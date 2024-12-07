#pragma once
#include "Object.h"
class Ground :
    public Object
{
public:
    Ground();
    ~Ground();
public:
    void Update() override;
    void Render(HDC _hdc) override;
};

