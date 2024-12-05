#pragma once
#include "Object.h"

class DiePanel :
    public Object
{
public:
	DiePanel();
	~DiePanel();
public:
	void Update() override;
	void Render(HDC _hdc) override;
private:
	vector<Object*> m_vObj;
};

