#include "Platform.h"
#include <iostream>

const sf::Vector2f Platform::size = sf::Vector2f(200, 10);
Ball* Platform::ball = nullptr;

bool intersects(sf::FloatRect rect, sf::CircleShape circle) {
	sf::Vector2f rectPos = rect.getPosition(), circlePos = circle.getPosition();
	sf::Vector2f dist = sf::Vector2f(
		abs(rectPos.x - circlePos.x),
		abs(rectPos.y - circlePos.y)
	);

	if(dist.x > rect.width / 2 + circle.getRadius()) return false;
	if(dist.y > rect.height / 2 + circle.getRadius()) return false;

	if(dist.x <= rect.width / 2) return true;
	if(dist.y <= rect.height / 2) return true;

	float cornerDist_sq = powf((dist.x - rect.width / 2), 2) + powf((dist.y - rect.height / 2), 2);
	return (cornerDist_sq <= circle.getRadius() * circle.getRadius());
}

Platform::Platform() {
	setSize(size);
	setOrigin(size / 2.f);
}

Platform::~Platform() {

}

void Platform::ballReflect(bool changeX) {
	if(ball != nullptr && cooldownClock.getElapsedTime().asMilliseconds() > 200) {
		if(intersects(sf::FloatRect(getPosition(), size), (sf::CircleShape)*ball)) {
			ball->velocity.y *= -1;
			if(changeX)
				ball->velocity.x = (ball->getPosition() - getPosition()).x * 0.01;
			cooldownClock.restart();
		}
	}
}

Player::Player() {
	setFillColor(sf::Color::Green);
}

void Player::update(float dt) {
	ballReflect(true);
}

Enemy::Enemy(unsigned int level) {
	setFillColor(sf::Color::Red);
}

void Enemy::update(float dt) {
	ballReflect(false);
	setPosition(ball->getPosition().x, getPosition().y);
}