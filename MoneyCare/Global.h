#pragma once
#include <SFML/Graphics.hpp>

class Global
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