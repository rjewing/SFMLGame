#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <SFML/Window/Event.hpp>
#include <SFML/Graphics/RenderWindow.hpp>


#include <map>
#include <memory>

#include "Command.hpp"
#include "Worker.hpp"

class CommandQueue;

class Player {
public:
	enum Action {
		// SelectWorker,
		SetWorkerTarget,
	};

public:
	Player();
	// Player(sf::RenderWindow& w);
	void handleEvent(const sf::Event& event, CommandQueue& commands);
	void handleRealtimeInput(CommandQueue& commands);

	void assignKey(Action action, sf::Keyboard::Key key);
	void assignMouseButton(Action action, sf::Mouse::Button button);
	sf::Keyboard::Key getAssignedKey(Action action) const;
	sf::Mouse::Button getAssignedButton(Action action) const;


private:
	void initializeActions();
	static bool isRealtimeAction(Action action);

private:
	std::map<sf::Keyboard::Key, Action> keyBinding;
	std::map<sf::Mouse::Button, Action> mouseBinding;
	std::map<Action, Command> actionBinding;

	// sf::RenderWindow& window;
	// std::vector<std::unique_ptr<Worker>> workers;
};

#endif /* PLAYER_HPP */
