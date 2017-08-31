#ifndef APPLICATION_HPP
#define APPLICATION_HPP

#include "ResourceHolder.hpp"
#include "ResourceIdentifiers.hpp"
#include "Player.hpp"
#include "StateStack.hpp"

#include <SFML/System/Time.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Text.hpp>

class Application {
public:
	Application();
	void run();

private:
	void processInput();
	void update(sf::Time dt);
	void render();

	void updateStatistics(sf::Time dt);
	void registerStates();

private:
	static const sf::Time TimePerFrame;

	sf::RenderWindow window;
	TextureHolder textures;
	FontHolder fonts;
	Player player;

	StateStack stateStack;

	sf::Text statisticsText;
	sf::Time statisticsUpdateTime;
	std::size_t statisticsNumFrames;
};

#endif /* APPLICATION_HPP */
