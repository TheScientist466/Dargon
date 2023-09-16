#include "Ball.h"

//sf::VideoMode* Ball::windowVidMode = nullptr;

Ball::Ball(float _rad) {
	setPointCount(64);
	setRadius(_rad);
	setOrigin(_rad, _rad);
}

void Ball::start() {
	started = true;
	velocity = sf::Vector2f(0, 500);
}

void Ball::update(float dt) {
	if(started) {
		move(velocity * dt);
	}
}