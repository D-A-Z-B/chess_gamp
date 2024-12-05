#pragma once
#include "Object.h"

class Text;
class Button :
    public Object
{
public:
    Button();
    ~Button();
public:
    void Update() override;
    void Render(HDC _hdc) override;
    void Init();
public:
    void SetText(Text* _text);
    void SetLoadingScene(wstring sceneName) { loadScene = sceneName; }
private:
    void OnClick();
    void ResizeText(float newSize);
private:
    Text* m_pText;
    RECT m_rect;
    wstring loadScene;
};