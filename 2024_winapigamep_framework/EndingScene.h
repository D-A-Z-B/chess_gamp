#pragma once
#include "Scene.h"
class EndingScene :
    public Scene
{
public:
    // Scene��(��) ���� ��ӵ�
    void Init() override;
    virtual void Render(HDC _hdc);
};

