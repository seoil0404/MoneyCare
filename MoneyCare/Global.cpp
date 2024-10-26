#include "Global.h"
#include "Coroutine.h"
#include "DebugLog.h"

sf::Clock Time::clock;

float Time::deltaTime;
const float Time::normalizeDeltaTime = 2000;

float Time::DeltaTime()
{
	return deltaTime;
}

void Time::ClockUpdate()
{
	deltaTime = clock.restart().asSeconds() * normalizeDeltaTime;

	//Debug::Log("DEBUG: Clock has been reset :" + std::to_string(deltaTime));

	Coroutine::AddCoroutine(ClockUpdate);
}