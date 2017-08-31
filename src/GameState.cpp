#include "GameState.hpp"

GameState::GameState(StateStack& stack, Context context) : State(stack, context), world(*context.window), player(*context.player) {}

void GameState::draw() {
    this->world.draw();
}

bool GameState::update(sf::Time dt) {
    this->world.update(dt);

    CommandQueue& commands = this->world.getCommandQueue();
    this->player.handleRealtimeInput(commands);

    return true;
}

bool GameState::handleEvent(const sf::Event& event) {
    CommandQueue& commands = this->world.getCommandQueue();
    this->player.handleEvent(event, commands);

    if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Right) {
		this->world.selectWorker();
	}

    // if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
    //     requestStackPush(States::Pause);

    return true;
}
