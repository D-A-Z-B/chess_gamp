#pragma once
#include "Object.h"

class Text;

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
	vector<Text*> m_txtObj;
	Text* gameOverTxt;
};

