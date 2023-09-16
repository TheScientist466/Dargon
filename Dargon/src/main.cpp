#include <SFML/Graphics.hpp>
#include <iostream>
#include "Platform.h"
#include "Ball.h"

void update(float deltaTime);
void start();
void end();
sf::RenderWindow* window;
sf::Event winEvents;
sf::FloatRect windowBox;
bool halted = true;

Ball ball(15);
Player p;
Enemy e(1);


int main() {
	sf::VideoMode vidM(1600, 900);
	window = new sf::RenderWindow(vidM, "Dargon", sf::Style::Close);
	sf::Clock deltaClock;
	windowBox = sf::FloatRect(sf::Vector2f(0, 0), (sf::Vector2f)window->getSize());

	//Ball::windowVidMode = &vidM;
	Platform::ball = &ball;
	p = Player();
	e = Enemy(0);


	p.setPosition(sf::Vector2f(window->getSize().x / 2, 0.9 * window->getSize().y));
	e.setPosition(sf::Vector2f(window->getSize().x / 2, 0.1 * window->getSize().y));
	ball.setPosition((sf::Vector2f)window->getSize() / 2.f);

	//window->setVerticalSyncEnabled(true);
	window->setFramerateLimit(200);
	while(window->isOpen()) {
		while(window->pollEvent(winEvents)) {
			switch(winEvents.type) {
			case sf::Event::Closed:
				window->close();
				break;
			case sf::Event::KeyPressed:
				if(winEvents.key.code == sf::Keyboard::Space && halted) {
					start();
				}
			}
		}
		float deltaTime = deltaClock.restart().asSeconds();
		update(deltaTime);
		window->clear();
		window->draw(e);
		window->draw(p);
		window->draw(ball);
		window->display();
	}
}

void start() {
	ball.start();
	halted = false;
}

void update(float deltaTime) {
	if(!halted) {
		ball.update(deltaTime);
		//if(ballPos.x < ball.getRadius() || ballPos.x > windowBox.width - ball.getRadius()) {
		//	ball.velocity.x *= -1;
		//}
		//if(ballPos.y < ball.getRadius() || ballPos.y > windowBox.height - ball.getRadius()) {
		//	ball.velocity.y *= -1;
		//}
		if(!windowBox.contains(ball.getPosition())) {
			end();
		}

		e.update(deltaTime);
		p.update(deltaTime);
		p.setPosition(sf::Mouse::getPosition(*window).x, p.getPosition().y);
	}
}

void end() {
	halted = true;
}