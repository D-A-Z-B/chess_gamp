#include "pch.h"
#include "Scene.h"
#include "Object.h"
#include "CollisionManager.h"
#include "TimeManager.h"
Scene::Scene()
	:m_executeTimer(0)
	, m_executeDelay(0.5f)
	, alphaPercent(150)
	, isAlphaBlend(false)
	, isUIBlending(false)
{
}

Scene::~Scene()
{
	Release();
}

void Scene::Init()
{
	isAlphaBlend = false;
}

void Scene::Update()
{
	for (UINT i = 0; i < (UINT)LAYER::END; ++i)
	{
		for (size_t j = 0; j < m_vecObj[i].size(); ++j)
		{
			if (!m_vecObj[i][j]->GetIsDead())
				m_vecObj[i][j]->Update();
		}
	}

	if (isAlphaBlend)
	{
		if (m_executeTimer < m_executeDelay)
			m_executeTimer += fDT;
		else
			m_executeTimer = m_executeDelay;
	}
}

void Scene::LateUpdate()
{
	for (size_t i = 0; i < (UINT)LAYER::END; i++)
	{
		for (UINT j = 0; j < m_vecObj[i].size(); ++j)
		{
			m_vecObj[i][j]->LateUpdate();
		}
	}
}

void Scene::Render(HDC _hdc)
{
	for (UINT i = 0; i < (UINT)LAYER::END; ++i)
	{
		for (size_t j = 0; j < m_vecObj[i].size();)
		{
			if (!m_vecObj[i][j]->GetIsDead())
				m_vecObj[i][j++]->Render(_hdc);
			else
				m_vecObj[i].erase(m_vecObj[i].begin() + j);
		}
	}

	AlphaBlendRender(_hdc);

	if(!isUIBlending)
	{
		for (size_t j = 0; j < m_vecObj[(UINT)LAYER::UI].size();)
		{
			m_vecObj[(UINT)LAYER::UI][j++]->Render(_hdc);
		}
	}
}

void Scene::AlphaBlendRender(HDC _hdc)
{
	if (!isAlphaBlend)
		return;

	HDC tempDC = CreateCompatibleDC(_hdc);
	HBITMAP tempBitmap = CreateCompatibleBitmap(_hdc, SCREEN_WIDTH, SCREEN_HEIGHT);
	HBITMAP oldBitmap = (HBITMAP)SelectObject(tempDC, tempBitmap);

	PatBlt(tempDC, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, color);

	float percent = m_executeTimer / m_executeDelay;

	BLENDFUNCTION bf = {};
	bf.BlendOp = AC_SRC_OVER;
	bf.BlendFlags = 0;
	bf.SourceConstantAlpha = static_cast<BYTE>(alphaPercent * percent);
	bf.AlphaFormat = 0;

	GdiAlphaBlend(
		_hdc, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT,
		tempDC, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT,
		bf
	);

	SelectObject(tempDC, oldBitmap);
	DeleteObject(tempBitmap);
	DeleteDC(tempDC);
}

void Scene::StartSceneBlending(float fadeTime, int percent, bool isUIBlend, DWORD color)
{
	isAlphaBlend = true;
	m_executeDelay = fadeTime;
	alphaPercent = percent;
	isUIBlending = isUIBlend;
	this->color = color;
}

void Scene::Release()
{
	// 오브젝트 삭제.
	for (size_t i = 0; i < (UINT)LAYER::END; i++)
	{
		for (UINT j = 0; j < m_vecObj[i].size(); ++j)
		{
			delete m_vecObj[i][j];
		}
		m_vecObj[i].clear();
	}
	GET_SINGLE(CollisionManager)->CheckReset();
}
