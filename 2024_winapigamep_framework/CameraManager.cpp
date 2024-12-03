#include "pch.h"
#include "CameraManager.h"

#include "TimeManager.h"

// Test
#include "InputManager.h"

void CameraManager::Init(Vec2 centerPos)
{
	this->centerPos = centerPos;
	shakingPos = centerPos;
	isShaking = false;
}

void CameraManager::Update()
{
	if (isShaking) {
		elapsedTime += fDT;
		shakingPos.x = centerPos.x + (rand() % shakeIntensity - 10);
		shakingPos.y = centerPos.y + (rand() % shakeIntensity - 10);

		if (elapsedTime >= shakeTime) {
			isShaking = false;
			shakingPos = centerPos;
		}
	}
}

void CameraManager::Shake(float intensity, float time)
{
	isShaking = true;
	shakeTime = time;
	shakeIntensity = intensity;
	elapsedTime = 0.f;
}