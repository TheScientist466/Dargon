#pragma once

#include <SFML/Graphics.hpp>

class Ball : public sf::CircleShape {
private:
	bool started = false;

public:
	sf::Vector2f velocity;
	const float speed = 500;
	Ball(float radius = 20);
	void start();
	void update(float deltaTime);
};