#pragma once
#include "Object.h"
class Aim :
    public Object
{
public:
	Aim();
	~Aim();
public:
	void Update() override;
	void Render(HDC _hdc) override;
};

