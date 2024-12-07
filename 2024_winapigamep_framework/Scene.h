#pragma once
//#include "Object.h"
class Object; // 클래스 전방선언
class Scene
{
public:
	Scene();
	virtual ~Scene(); // 가상 소멸자
public:
	virtual void Init();
	virtual void Update();
	virtual void LateUpdate();
	virtual void Render(HDC _hdc);
	virtual void Release();
public:
	void AddObject(Object* _obj, LAYER _type)
	{
		m_vecObj[(UINT)_type].push_back(_obj);
	}
	const vector<Object*>& GetLayerObjects(LAYER _type)
	{
		return m_vecObj[(UINT)_type];
	}
	void StartSceneBlending(float fadeTime, int percent, bool isUiBlend, DWORD color = BLACKNESS);
private:
	void AlphaBlendRender(HDC _hdc);
private:
	vector<Object*> m_vecObj[(UINT)LAYER::END];
	HDC m_tempDC;
	HBITMAP m_tempBitmap;
	HBITMAP m_oldBitmap;

	float m_executeTimer;
	float m_executeDelay;
	int alphaPercent;
	bool isAlphaBlend;
	bool isUIBlending;
	DWORD color;
};

