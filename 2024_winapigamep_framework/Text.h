#pragma once
#include "Object.h"
class Text : public Object {
public:
    Text();
    ~Text();
public:
    void Init();
public:
    void Update() override;
    void Render(HDC _hdc) override;
public:
    void SetText(const std::wstring& text) { currentText = text; }
    void SetColor(COLORREF color) { currentColor = color; }
    bool LoadFont(const std::wstring& fontPath, wstring fontName, int height = 24, int weight = FW_NORMAL);
public:
    wstring GetCurrentText() { return currentText; }
    wstring GetExecutableDirectory();
private:
    std::wstring currentText;
    COLORREF currentColor = RGB(0, 0, 0);
    HFONT currentFont = nullptr;
    std::wstring loadedFontPath;
};

