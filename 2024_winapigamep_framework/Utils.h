#pragma once
class Utils
{
public:
    static void RenderRect(HDC _hdc, Vec2 _pos, __int32 _width, __int32 _height);
    static void RenderRectColor(HDC _hdc, Vec2 _pos, __int32 _width, __int32 _height, COLORREF _color);
    static void RenderCircle(HDC _hdc, Vec2 _pos, __int32 _radius);
    static void RenderCircleColor(HDC _hdc, Vec2 _pos, __int32 _radius, COLORREF _color);
    static void RenderLine(HDC _hdc, Vec2 _from, Vec2 _to);
    static void RenderLineColor(HDC _hdc, Vec2 _from, Vec2 _to, COLORREF _color);
};