#pragma once

#include <SFML/Graphics.hpp>
#include "Ball.h"

class Platform : public sf::RectangleShape {
public:
	Platform();
	~Platform();
	virtual void update(float deltaTime) = 0;
	
	static const sf::Vector2f size;
	static Ball* ball;
};

class Player : public Platform {
public:
	Player();

	void update(float deltaTime);
};

class Enemy : public Platform {
public:
	Enemy(unsigned int level);

	void update(float deltaTime);
};