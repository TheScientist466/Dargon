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
	//std::cout << dist.x << ", " << dist.y << std::endl;

	if(dist.x < rect.width / 2 && dist.y < rect.height / 2 )
		return true;
	return false;
}

Platform::Platform() {
	setSize(size);
	setOrigin(size / 2.f);
}

Platform::~Platform() {

}

Player::Player() {
	setFillColor(sf::Color::Green);
}

void Player::update(float dt) {
	if(sf::FloatRect(getPosition(), size).contains(ball->getPosition())) {
		ball->velocity.y *= -1;
	}
}

Enemy::Enemy(unsigned int level) {
	setFillColor(sf::Color::Red);
}

void Enemy::update(float dt) {
	if(intersects(sf::FloatRect(getPosition(), size), (sf::CircleShape)*ball)) {
		ball->velocity.y *= -1;
	}
}