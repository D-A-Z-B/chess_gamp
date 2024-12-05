#pragma once
#include "Scene.h"

class Background;
class Text;
class TitleScene : public Scene
{
public:
	~TitleScene();
public:
	// Scene��(��) ���� ��ӵ�
	virtual void Init() override;
	virtual void Update() override;
private:
	void NextSceneRoutine();
private:
	vector<Background*>vecBackground;
	vector<Text*> vecButtons;
private:
	int currentSelectedNumber = 0;

	bool isNextScene = false;
};

