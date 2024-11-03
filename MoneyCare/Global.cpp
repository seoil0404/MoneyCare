#include "Global.h"
#include "Coroutine.h"
#include "DebugLog.h"

sf::Clock Global::clock;

float Global::deltaTime;
const float Global::normalizeDeltaTime = 160;

float Global::DeltaTime()
{
	return deltaTime;
}

void Global::ClockUpdate()
{
	deltaTime = clock.restart().asSeconds() * normalizeDeltaTime;

	Coroutine::AddCoroutine(
		[]() {
			Global::ClockUpdate();
		}
	);
}