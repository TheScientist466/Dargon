#include "Ball.h"

//sf::VideoMode* Ball::windowVidMode = nullptr;

sf::Vector2f normalize(sf::Vector2f v) {
	return (v / sqrtf(v.x * v.x + v.y * v.y));
}

Ball::Ball(float _rad) {
	setPointCount(64);
	setRadius(_rad);
	setOrigin(_rad, _rad);
}

void Ball::start() {
	started = true;
	velocity = sf::Vector2f(0, -1);
}

void Ball::update(float dt) {
	if(started) {
		move(normalize(velocity) * dt * speed);
	}
}