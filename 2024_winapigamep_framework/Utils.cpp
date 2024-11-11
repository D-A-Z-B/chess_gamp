#include "pch.h"
#include "Utils.h"

void Utils::RenderRect(HDC _hdc, Vec2 _pos, __int32 _width, __int32 _height)
{
    ::Rectangle(_hdc
        , _pos.x - _width / 2
        , _pos.y - _height / 2
        , _pos.x + _width / 2
        , _pos.y + _height / 2
    );
}

void Utils::RenderRectColor(HDC _hdc, Vec2 _pos, __int32 _width, __int32 _height, COLORREF _color)
{
    HBRUSH hBrush = ::CreateSolidBrush(_color);
    HBRUSH hOldBrush = (HBRUSH)::SelectObject(_hdc, hBrush);

    ::Rectangle(_hdc
        , _pos.x - _width / 2
        , _pos.y - _height / 2
        , _pos.x + _width / 2
        , _pos.y + _height / 2
    );
    ::SelectObject(_hdc, hOldBrush);
    ::DeleteObject(hBrush);
}

void Utils::RenderCircle(HDC _hdc, Vec2 _pos, __int32 _radius)
{
    ::Ellipse(_hdc
        , _pos.x - _radius / 2
        , _pos.y - _radius / 2
        , _pos.x + _radius / 2
        , _pos.y + _radius / 2
    );

}

void Utils::RenderCircleColor(HDC _hdc, Vec2 _pos, __int32 _radius, COLORREF _color)
{
    HBRUSH hBrush = ::CreateSolidBrush(_color);
    HBRUSH hOldBrush = (HBRUSH)::SelectObject(_hdc, hBrush);

    ::Ellipse(_hdc
        , _pos.x - _radius / 2
        , _pos.y - _radius / 2
        , _pos.x + _radius / 2
        , _pos.y + _radius / 2
    );
    ::SelectObject(_hdc, hOldBrush);
    ::DeleteObject(hBrush);
}

void Utils::RenderLine(HDC _hdc, Vec2 _from, Vec2 _to)
{
    ::MoveToEx(_hdc, _from.x, _from.y, nullptr);
    ::LineTo(_hdc, _to.x, _to.y);
}

void Utils::RenderLineColor(HDC _hdc, Vec2 _from, Vec2 _to, COLORREF _color)
{
    HPEN hPen = ::CreatePen(PS_SOLID, 1, _color);
    HPEN hOldPen = (HPEN)::SelectObject(_hdc, hPen);
    ::MoveToEx(_hdc, _from.x, _from.y, nullptr);
    ::LineTo(_hdc, _to.x, _to.y);

    ::SelectObject(_hdc, hOldPen);
    ::DeleteObject(hPen);

}