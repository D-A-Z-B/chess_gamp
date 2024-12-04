#pragma once
#include "Object.h"

#include "ResourceManager.h"

class Texture;
class Background :
    public Object
{
public:
    Background();
    ~Background();
public:
    void SetBackgroundTexture(wstring texture) { m_pTex = GET_SINGLE(ResourceManager)->TextureLoad(texture, L"Texture\\Background\\" + texture + L".bmp"); }
public:
    void Update() override;
    void Render(HDC _hdc) override;
private:
    Texture* m_pTex;
};

