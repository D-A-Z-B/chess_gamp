#include "pch.h"
#include "Text.h"

#include "GDISelector.h"

Text::Text() : currentFont(nullptr), loadedFontPath(L"")
{
}

Text::~Text()
{
    RemoveFontResourceEx(loadedFontPath.c_str(), FR_PRIVATE, NULL);
}

void Text::Init()
{
}

void Text::Update()
{
}

void Text::Render(HDC _hdc)
{
    Vec2 vPos = GetPos();
    Vec2 vSize = GetSize();

    SetTextColor(_hdc, currentColor);
    GDISelector font(_hdc, currentFont);

    SIZE textSize;
    GetTextExtentPoint32(_hdc, currentText.c_str(), static_cast<int>(currentText.size()), &textSize);

    int x = static_cast<int>(vPos.x - textSize.cx / 2);
    int y = static_cast<int>(vPos.y - textSize.cy / 2);

    TextOut(_hdc, x, y, currentText.c_str(), static_cast<int>(currentText.size()));
}


bool Text::LoadFont(const wstring& fontPath, wstring fontName, int height, int weight) {
    if (AddFontResourceEx(fontPath.c_str(), FR_PRIVATE, NULL) == 0) {
        return false;
    }

    loadedFontPath = fontPath;

    if (currentFont) {
        DeleteObject(currentFont);
    }

    currentFont = CreateFont(
        height,
        0,
        0,
        0,
        weight,
        FALSE,
        FALSE,
        FALSE,
        DEFAULT_CHARSET,
        OUT_DEFAULT_PRECIS,
        CLIP_DEFAULT_PRECIS,
        DEFAULT_QUALITY,
        DEFAULT_PITCH | FF_SWISS,
        fontName.c_str()
    );

    return true;
}

wstring Text::GetExecutableDirectory()
{
    wchar_t buffer[MAX_PATH];
    GetModuleFileName(nullptr, buffer, MAX_PATH);

    // 전체 경로에서 실행 파일의 디렉토리만 추출
    std::wstring exePath(buffer);
    size_t pos = exePath.find_last_of(L"\\/");
    if (pos != std::wstring::npos) {
        return exePath.substr(0, pos);
    }
    return L""; // 실패 시 빈 문자열 반환
}
