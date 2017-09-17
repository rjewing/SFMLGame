#include "Application.hpp"
#include "State.hpp"
#include "StateIdentifiers.hpp"
#include "TitleState.hpp"
#include "GameState.hpp"
#include "MenuState.hpp"
#include "PauseState.hpp"

#include <iostream>

const sf::Time Application::TimePerFrame = sf::seconds(1.f/60.f);

Application::Application() :
window(sf::VideoMode::getDesktopMode(), "States", sf::Style::Close),
textures(),
fonts(),
player(this->window),
stateStack(State::Context(this->window, this->textures, this->fonts, this->player)),
statisticsText(),
statisticsUpdateTime(),
statisticsNumFrames(0)
{
	this->window.setKeyRepeatEnabled(false);
	this->window.setFramerateLimit(60);
	this->fonts.load(Fonts::Main, "media/Sansation.ttf");
	this->textures.load(Textures::TitleScreen, "media/textures/WorldMap.png");

	this->statisticsText.setFont(this->fonts.get(Fonts::Main));
	this->statisticsText.setPosition(5.f, 5.f);
	this->statisticsText.setCharacterSize(10u);

	registerStates();
	this->stateStack.pushState(States::Title);
}

void Application::run() {
	sf::Clock clock;
	sf::Time timeSinceLastUpdate = sf::Time::Zero;

	while (this->window.isOpen()) {
		sf::Time dt = clock.restart();
		timeSinceLastUpdate += dt;
		while (timeSinceLastUpdate > TimePerFrame) {
			timeSinceLastUpdate -= TimePerFrame;

			processInput();
			update(TimePerFrame);

			if (this->stateStack.isEmpty())
				this->window.close();

		}

		updateStatistics(dt);
		render();
	}
}

void Application::processInput() {
	sf::Event event;
	while (this->window.pollEvent(event)) {
		this->stateStack.handleEvent(event);

		if (event.type == sf::Event::Closed)
			this->window.close();
	}
}

void Application::update(sf::Time dt) {
	this->stateStack.update(dt);
}

void Application::render() {
	this->window.clear();

	this->stateStack.draw();

	this->window.setView(this->window.getDefaultView());
	this->window.draw(this->statisticsText);

	this->window.display();
}

void Application::updateStatistics(sf::Time dt) {
	this->statisticsUpdateTime += dt;
	this->statisticsNumFrames += 1;
	if (this->statisticsUpdateTime >= sf::seconds(1.0f)) {
		this->statisticsText.setString("FPS: " + std::to_string(this->statisticsNumFrames));

		this->statisticsUpdateTime -= sf::seconds(1.0f);
		this->statisticsNumFrames = 0;
	}
}

void Application::registerStates() {
	this->stateStack.registerState<TitleState>(States::Title);
	this->stateStack.registerState<MenuState>(States::Menu);
	this->stateStack.registerState<GameState>(States::Game);
	this->stateStack.registerState<PauseState>(States::Pause);
}
