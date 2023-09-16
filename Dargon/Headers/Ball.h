#pragma once

#include <SFML/Graphics.hpp>

class Ball : public sf::CircleShape {
private:
	bool started = false;

public:
	//static sf::VideoMode* windowVidMode;
	sf::Vector2f velocity;
	Ball(float radius = 20);
	void start();
	void update(float deltaTime);
};