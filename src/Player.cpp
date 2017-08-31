#include <map>
#include <string>
#include <algorithm>
#include <memory>

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/RenderTarget.hpp>

#include "Player.hpp"
#include "CommandQueue.hpp"
#include "Worker.hpp"

// struct WorkerMover {
// 	WorkerMover(sf::RenderWindow& w) : window(w) {}
//
// 	void operator() (Worker& worker, sf::Time) const {
// 		worker.setWorkLocation(sf::Vector2f(sf::Mouse::getPosition(this->window)));
// 		worker.deselect();
// 	}
//
// 	sf::RenderWindow& window;
// };

// Player::Player() {
// 	this->mouseBinding[sf::Mouse::Left] = SetWorkerTarget;
//
// 	initializeActions();
//
// 	for (auto& pair : this->actionBinding)
// 		pair.second.category = Category::Player;
// }

Player::Player(sf::RenderWindow& w) : window(w){
	// this->mouseBinding[sf::Mouse::Left] = SelectWorker;
	this->mouseBinding[sf::Mouse::Left] = SetWorkerTarget;

	initializeActions();

	for (auto& pair : this->actionBinding)
		pair.second.category = Category::SelectedWorker;
}

void Player::handleEvent(const sf::Event& event, CommandQueue& commands) {
	if (event.type == sf::Event::KeyPressed) {
		auto found = this->keyBinding.find(event.key.code);
		if (found != this->keyBinding.end() && !isRealtimeAction(found->second))
			commands.push(this->actionBinding[found->second]);
	}

	else if (event.type == sf::Event::MouseButtonPressed) {
		auto found = this->mouseBinding.find(event.mouseButton.button);
		if (found != this->mouseBinding.end() && !isRealtimeAction(found->second))
			commands.push(this->actionBinding[found->second]);
	}
}

void Player::handleRealtimeInput(CommandQueue& commands) {
	for (auto pair : this->keyBinding) {
		if (sf::Keyboard::isKeyPressed(pair.first) && isRealtimeAction(pair.second))
			commands.push(this->actionBinding[pair.second]);
	}
}

void Player::assignKey(Action action, sf::Keyboard::Key key) {
	for (auto itr = this->keyBinding.begin(); itr != this->keyBinding.end(); ) {
		if (itr->second == action)
			this->keyBinding.erase(itr++);
		else
			itr++;
	}
	for (auto itr = this->mouseBinding.begin(); itr != this->mouseBinding.end(); ) {
		if (itr->second == action)
			this->mouseBinding.erase(itr++);
		else
			itr++;
	}
	this->keyBinding[key] = action;
}

void Player::assignMouseButton(Action action, sf::Mouse::Button button) {
	for (auto itr = this->keyBinding.begin(); itr != this->keyBinding.end(); ) {
		if (itr->second == action)
			this->keyBinding.erase(itr++);
		else
			itr++;
	}
	for (auto itr = this->mouseBinding.begin(); itr != this->mouseBinding.end(); ) {
		if (itr->second == action)
			this->mouseBinding.erase(itr++);
		else
			itr++;
	}
	this->mouseBinding[button] = action;
}

sf::Keyboard::Key Player::getAssignedKey(Action action) const {
	for (auto pair : this->keyBinding) {
		if (pair.second == action)
			return pair.first;
	}

	return sf::Keyboard::Unknown;
}

sf::Mouse::Button Player::getAssignedButton(Action action) const {
	for (auto pair : this->mouseBinding) {
		if (pair.second == action)
			return pair.first;
	}
	return sf::Mouse::ButtonCount;
}

void Player::initializeActions() {
	// this->actionBinding[SelectWorker].action = derivedAction<Worker>( [] (Worker& w, sf::Time) {w.setCategory(Category::SelectedWorker)};

	this->actionBinding[SetWorkerTarget].action = derivedAction<Worker>( [this] (Worker& w, sf::Time) { w.setWorkLocation(sf::Vector2f(sf::Mouse::getPosition(window))); });
}

bool Player::isRealtimeAction(Action action) {
	switch (action) {
		// case SelectWorker:
		case SetWorkerTarget:
			return false;

		default:
			return false;
	}
}
