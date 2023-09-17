#include <SFML/Graphics.hpp>
#include <future>
#include <deque>
#include <imgui-SFML.h>
#include <imgui.h>

#include "Platform.h"
#include "Ball.h"
#include "Sensor.h"

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
int enemyLevel = 0;

std::deque<float> playerPosSamples;

bool useMouse = false;
float smoothness = 75.f;

int main() {
	sf::VideoMode vidM(1600, 900);
	window = new sf::RenderWindow(vidM, "Dargon", sf::Style::Close);
	ImGui::SFML::Init(*window);
	sf::Clock deltaClock;
	windowBox = sf::FloatRect(sf::Vector2f(0, 0), (sf::Vector2f)window->getSize());

	//Ball::windowVidMode = &vidM;
	Platform::ball = &ball;
	p = Player();
	e = Enemy(0);


	p.setPosition(sf::Vector2f(window->getSize().x / 2, 0.9 * window->getSize().y));
	e.setPosition(sf::Vector2f(window->getSize().x / 2, 0.1 * window->getSize().y));
	ball.setPosition((sf::Vector2f)window->getSize() / 2.f);

	//std::thread t(pollSensorVal);
	std::future<void> fut = std::async(pollSensorVal);

	window->setVerticalSyncEnabled(true);
	//window->setFramerateLimit(200);
	while(window->isOpen()) {
		while(window->pollEvent(winEvents)) {
			ImGui::SFML::ProcessEvent(*window, winEvents);
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
		sf::Time deltaTime = deltaClock.restart();
		float deltaTimeS = deltaTime.asSeconds();
		ImGui::SFML::Update(*window, deltaTime);
		update(deltaTimeS);

		ImGui::Begin("Setup", NULL, ImGuiWindowFlags_NoMove);
		ImGui::SetWindowPos(ImVec2(0, 0));
		if(halted)
			ImGui::Text("Press Spacebar to start playing");
		ImGui::SliderInt("Enemy Level", &e.level, 0, 5, e.level < 1 ? "noob" : e.level > 4 ? "IMPOSSIBLE" : "%d");
		ImGui::Checkbox("Use Mouse", &useMouse);
		if(!useMouse) {
			if(ImGui::SliderFloat("Smoothness", &smoothness, 20.f, 100.f, "%.0f")) {
				playerPosSamples.clear();
			}
		}
		ImGui::End();

		window->clear();
		window->draw(e);
		window->draw(p);
		window->draw(ball);
		ImGui::SFML::Render(*window);
		window->display();
	}
	ImGui::SFML::Shutdown();
	delete window;
	terminate();
	fut.get();
}

void start() {
	ball.start();
	halted = false;
}

void update(float deltaTime) {
	if(!halted) {
		ball.update(deltaTime);
		sf::Vector2f ballPos = ball.getPosition();
		if(ballPos.x < ball.getRadius() || ballPos.x >= windowBox.width - ball.getRadius()) {
			ball.velocity.x *= -1;
		}

		if(!windowBox.contains(ball.getPosition())) {
			end();
		}

		e.update(deltaTime);
		p.update(deltaTime);

		if(useMouse) {
			p.setPosition(sf::Mouse::getPosition(*window).x, p.getPosition().y);
		}
		else {
			playerPosSamples.push_back(getSensorVal());
			if(playerPosSamples.size() == (int)smoothness) {
				float sum = 0;
				for(float s : playerPosSamples) {
					sum += s;
				}
				p.setPosition(sum * 75 / playerPosSamples.size(), p.getPosition().y);
				playerPosSamples.pop_front();
			}
		}
	}
}

void end() {
	halted = true;
	p.setPosition(sf::Vector2f(window->getSize().x / 2, 0.9 * window->getSize().y));
	e.setPosition(sf::Vector2f(window->getSize().x / 2, 0.1 * window->getSize().y));
	ball.setPosition((sf::Vector2f)window->getSize() / 2.f);
}