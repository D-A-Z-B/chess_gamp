#pragma once
class CameraManager
{
	DECLARE_SINGLE(CameraManager);
public:
	void Init(Vec2 centerPos);
	void Update();
public:
	void Shake(float intensity,float time);
public:
	const Vec2& GetCenter() const { return centerPos; }
	const Vec2& GetShakingPos() const { return shakingPos; }
public:
	Vec2 centerPos;
	Vec2 shakingPos;

	int shakeIntensity;
	float elapsedTime;
	float shakeDuration;

	bool isShaking;
};

