#pragma once
#include "Object.h"

class Texture;

class Aim :
    public Object
{
public:
	Aim();
	~Aim();
public:
	void Update() override;
	void Render(HDC _hdc) override;
private:
	Texture* m_pTex;
};

