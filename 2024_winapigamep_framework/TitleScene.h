#pragma once
#include "Scene.h"

class Background;
class Text;
class TitleScene : public Scene
{
public:
	~TitleScene();
public:
	// Scene을(를) 통해 상속됨
	virtual void Init() override;
	virtual void Update() override;
private:
	vector<Background*>vecBackground;
	vector<Text*> vecButtons;
private:
	int currentSelectedNumber = 0;
};

