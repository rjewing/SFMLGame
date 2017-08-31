#include <SFML/Graphics.hpp>
#include "Game.hpp"

const sf::Time Game::TimePerFrame = sf::seconds(1.f/60.f);


Game::Game() : window(sf::VideoMode::getDesktopMode(), "World", sf::Style::Close)
, world(this->window)
, font()
, statisticsText()
, statisticsUpdateTime()
, statisticsNumFrames(0)
, player() {
	this->window.setFramerateLimit(60);
	this->font.loadFromFile("media/Sansation.ttf");
	this->statisticsText.setFont(this->font);
	this->statisticsText.setPosition(5.f, 5.f);
	this->statisticsText.setCharacterSize(10);

}

void Game::run() {
	sf::Clock clock;
	sf::Time timeSinceLastUpdate = sf::Time::Zero;
	while(this->window.isOpen()) {
		sf::Time elapsedTime = clock.restart();
		timeSinceLastUpdate += elapsedTime;
		while (timeSinceLastUpdate > TimePerFrame) {
			timeSinceLastUpdate -= TimePerFrame;

			processInput();
			update(TimePerFrame);
		}
		updateStatistics(elapsedTime);
		render();
	}
}

void Game::processInput() {
	CommandQueue& commands = this->world.getCommandQueue();

	sf::Event event;
	while (this->window.pollEvent(event)) {
	this->player.handleEvent(event, commands);
	if (event.type == sf::Event::Closed)
		this->window.close();
	}

	this->player.handleRealtimeInput(commands);

	if (sf::Mouse::isButtonPressed(sf::Mouse::Right)) {
		this->world.selectWorker();
	}
}

void Game::update(sf::Time elapsedTime) {
	this->world.update(elapsedTime);
}

void Game::render() {
	this->window.clear(sf::Color::Black);
	this->world.draw();

	this->window.setView(this->window.getDefaultView());
	this->window.draw(this->statisticsText);
	this->window.display();
}

void Game::updateStatistics(sf::Time elapsedTime) {
	this->statisticsUpdateTime += elapsedTime;
	this->statisticsNumFrames += 1;

	sf::Vector2i mpos = sf::Mouse::getPosition(this->window);
	sf::Vector2f workerpos = this->world.worker->getPosition();

	if (this->statisticsUpdateTime >= sf::seconds(1.0f)) {
		this->statisticsText.setString(
			"Frames / Second = " + std::to_string(this->statisticsNumFrames) + "\n" +
			"Time / Update = " + std::to_string(this->statisticsUpdateTime.asMicroseconds() / this->statisticsNumFrames) + "us" +"\n" +
			std::to_string(mpos.x) + " " + std::to_string(mpos.y) + "\n" +
			std::to_string(workerpos.x) + " " + std::to_string(workerpos.y));

		this->statisticsUpdateTime -= sf::seconds(1.0f);
		this->statisticsNumFrames = 0;
	}
}
