#pragma once
#include "Scene.h"

class Text;
class ClearScene :
    public Scene
{
public:
    void Init() override;
    void Update() override;
    void Render(HDC _hdc) override;
private:
    void StartRoutine();
    void ButtonRoutine();
    void NormalRoutine();
private:
    float easeOutElastic(float t);
private:
    bool isStart = false;
    bool isButton = false;

    int currentSelectedNumber = 0;

    Text* titleText;
    vector<Text*> vecButtons;
};

