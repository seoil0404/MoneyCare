#pragma once
#include <SFML/Graphics.hpp>
#include "WindowManager.h"
#include "Coroutine.h"
#include "DebugLog.h"
#include "string"

class Time
{
public:
	static float DeltaTime();

private:
	static void ClockUpdate();
	
	static sf::Clock clock;

	static const float normalizeDeltaTime;
	static float deltaTime;

	friend int main();
};